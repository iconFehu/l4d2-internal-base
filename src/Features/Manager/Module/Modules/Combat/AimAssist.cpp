#include "AimAssist.h"
#include "../../../RotationManager.h"
namespace F::AimAssistModule
{
	inline IClientEntity* target = nullptr;
	inline Vector startViewAngles = Vector(), renderVector = Vector();
	inline bool ShouldRun(C_TerrorPlayer* pLocal, C_TerrorWeapon* pWeapon, CUserCmd* cmd)
	{
		if ((cmd->buttons & IN_USE))
			return false;

		if (pLocal->m_isHangingFromLedge() || pLocal->m_isHangingFromTongue() || !pLocal->CanAttackFull())
			return false;

		//You could also check if the current spread is -1.0f and not run nospread I guess.
		//But since I wanted to filter out shotungs and just be sure that it isnt ran for other stuff I check the weaponid.

		switch (pWeapon->GetWeaponID())
		{
		case WEAPON_AK47:
		case WEAPON_AWP:
		case WEAPON_DEAGLE:
		case WEAPON_HUNTING_RIFLE:
		case WEAPON_M16A1:
		case WEAPON_M60:
		case WEAPON_MAC10:
		case WEAPON_MILITARY_SNIPER:
		case WEAPON_MP5:
		case WEAPON_PISTOL:
		case WEAPON_SCAR:
		case WEAPON_SCOUT:
		case WEAPON_SSG552:
		case WEAPON_UZI:
		case WEAPON_AUTO_SHOTGUN:
		case WEAPON_SPAS:
		case WEAPON_PUMP_SHOTGUN:
		case WEAPON_CHROME_SHOTGUN:
			return true;
		default:
			break;
		}

		return false;
	}
	inline Vector getHitBoxPos(IClientEntity* pEntity, C_TerrorPlayer* pLocal)
	{
		Vector box = Vector();
		ClientClass* pCC = pEntity->GetClientClass();
		Vector vCamera;
		I::EngineClient->GetViewAngles(vCamera);
		switch (pCC->m_ClassID)
		{
		case EClientClass::Tank:
		{
			C_BaseAnimating* pPlayer = pEntity->As<C_BaseAnimating*>();
			box = pPlayer->GetHitboxPositionNearestPosition(HITGROUP_CHEST, pLocal->Weapon_ShootPosition(), vCamera);
			break;
		}
		case EClientClass::Witch:
		{
			C_BaseAnimating* pPlayer = pEntity->As<C_BaseAnimating*>();
			box = pPlayer->GetHitboxPositionNearestPosition(HITGROUP_HEAD, pLocal->Weapon_ShootPosition(), vCamera);
			break;
		}
		case EClientClass::Boomer:
		case EClientClass::Jockey:
		case EClientClass::Smoker:
		case EClientClass::Hunter:
		case EClientClass::Spitter:
		case EClientClass::Charger:
		{
			C_BaseAnimating* pPlayer = pEntity->As<C_BaseAnimating*>();
			int hit = HITGROUP_HEAD;
			if (pCC->m_ClassID == EClientClass::Boomer) { hit = HITGROUP_STOMACH; };
			box = pPlayer->GetHitboxPositionNearestPosition(hit, pLocal->Weapon_ShootPosition(), vCamera);
			break;
		}
		case EClientClass::Infected:
		{
			C_BaseAnimating* pInfected = pEntity->As<C_BaseAnimating*>();
			box = pInfected->GetHitboxPositionNearestPosition(HITGROUP_STOMACH, pLocal->Weapon_ShootPosition(), vCamera);
			break;
		}
		default:
		{
			break;
		}
		}
		if (!box.IsZero()) {
			return box;
		}
		return Vector();
	}
	namespace Config
	{
		inline float maxfov = 15.0f;
	}
	void AimAssist::onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal)
	{
		if (!ShouldRun(pLocal, pWeapon, cmd))
		{	
			return;
		}
		renderVector = Vector();
		//FindTarget
		if (target == nullptr)
		{
			startViewAngles = Vector();
			target = Utils::target.find(pLocal, Config::maxfov);
			if (target == nullptr)
				return;
		}
		else {
			bool isDead = Utils::target.CheckInvaidOrDead(pLocal, target);
			if (isDead)
			{
				target = nullptr;
				return;
			}
		}
		//After M1
		if (cmd->buttons & IN_ATTACK && target != nullptr)
		{
			if (startViewAngles.IsZero())
			{
				I::EngineClient->GetViewAngles(startViewAngles);
			}
			//Rotate to target
			Vector pLocalPos = pLocal->Weapon_ShootPosition();
			C_BaseAnimating* pAnimating = target->As<C_BaseAnimating*>();
			Vector destination = getHitBoxPos(target, pLocal);
			Vector aimpos = U::Math.GetAngleToPosition(pLocalPos, destination);
			float distanceToStart = U::Math.GetFovBetween(startViewAngles,aimpos);
			float distanceToCurrent = U::Math.GetFovBetween(cmd->viewangles, aimpos);
			float factor = (distanceToStart - distanceToCurrent) / distanceToStart;
			startViewAngles.x += (aimpos.x - startViewAngles.x) * U::Math.Max(0.0f,U::Math.Min(1.0f, factor));
			cmd->viewangles.x = startViewAngles.x;
			Helper::rotationManager.setTargetRotation(cmd->viewangles, 1);
			renderVector = cmd->viewangles;
			I::EngineClient->SetViewAngles(cmd->viewangles);
		}
	}

	void AimAssist::onPostCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal)
	{
	}

	void AimAssist::onRender2D()
	{
		if (!I::EngineClient->IsInGame()) {
			target = nullptr;
			return;
		};
		if (I::EngineVGui->IsGameUIVisible()) { return; }
		C_TerrorPlayer* pLocal = I::ClientEntityList->GetClientEntity(I::EngineClient->GetLocalPlayer())->As<C_TerrorPlayer*>();
		if (renderVector.IsZero()) return;
		Vector vec = U::Math.AngleVectors(renderVector);
		Vector vViewAngleOnWorld = pLocal->Weapon_ShootPosition() + (vec * 1400.0f);
		Vector screen;
		G::Util.W2S(vViewAngleOnWorld, screen);
		G::Draw.Circle(screen.x, screen.y, 2, 8, Color(255, 255, 255, 255));
	}

	void AimAssist::onEnabled()
	{
	}

	void AimAssist::onDisabled()
	{
	}
}
