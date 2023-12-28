#include "BunnyHop.h"
namespace F {
	namespace BHop {
		void BunnyHop::onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal)
		{
			if ((cmd->buttons & IN_JUMP) && !(pLocal->m_fFlags() & FL_ONGROUND))
					cmd->buttons &= ~IN_JUMP;
		}

		void BunnyHop::onRender2D()
		{
		}
	}
}
