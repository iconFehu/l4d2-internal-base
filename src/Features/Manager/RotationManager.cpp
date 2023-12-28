#include "RotationManager.h"
#include "random"
inline Vector lastRotation = Vector();
inline float getAngleDifference(float a, float b) {
	return (
		std::fmod(
			std::fmod(a - b, 360.f) + 540.f
			, 360.f)
		) - 180.f;
}

bool Helper::RotationManager::hasKeepRotationReachedLimit() {
	return I::GlobalVars->realtime - lastMS >= keepRotation / 1000;
}

bool Helper::RotationManager::ShouldDisabledRotation()
{
	if (!hasKeepRotationReachedLimit()) return false;
	return DisabledRotation || hypot(getAngleDifference(target.y, current.y), target.x - current.x) < 1;
}

void Helper::RotationManager::calcRotation()
{
	if (DisabledRotation) {
		return;
	}
	Vector diffRotation = target - current;
	U::Math.ClampAngles(diffRotation);
	float rotationDiff = hypot(getAngleDifference(target.y, current.y), diffRotation.x);
	double min = 3.0, max = 7.0;
	float supposedTurnSpeed = 35;
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(min, max);
	double nextGassain = distribution(generator);
	float realisticTurnSpeed = rotationDiff * (U::Math.Min<float>(supposedTurnSpeed + acceletion, 180.0f) / 180.0f);
	if (rotationDiff > 30)
	{
		float a1 = (-cos(rotationDiff / 180.f * M_PI) * 0.5f + 0.5f);
		float a2 = (1.f - (-cos(rotationDiff / 180.f * M_PI) * 0.5f + 0.5f));
		realisticTurnSpeed = static_cast<float>(pow(a1, 2.0)) * 30 + static_cast<float>(pow(a2, 2.0)) * 20;
		acceletion = 0;
	}
	else {
		acceletion += nextGassain;
	}
	if (diffRotation.x > realisticTurnSpeed)
	{
		diffRotation.x = realisticTurnSpeed;
	}
	else {
		diffRotation.x = U::Math.Max(diffRotation.x, -realisticTurnSpeed);
	}
	if (diffRotation.y > realisticTurnSpeed)
	{
		diffRotation.y = realisticTurnSpeed;
	}
	else {
		diffRotation.y = U::Math.Max(diffRotation.y, -realisticTurnSpeed);
	}
	U::Math.ClampAngles(diffRotation);
	current = current + diffRotation;
	U::Math.ClampAngles(current);
	acceletion = hypot(getAngleDifference(target.y, current.y), target.x - current.x) <= 0 ? 0 : acceletion;
}

void Helper::RotationManager::onUpdate()
{
	if (!I::EngineClient->IsInGame()) {
		current = Vector();
		target = Vector();
		keepRotation = 0;
		DisabledRotation = true;
		acceletion = 0;
		return;
	}
	
	Vector viewAngles;
	I::EngineClient->GetViewAngles(viewAngles);
	if (current.IsZero()) {
		current = viewAngles;
		return;
	}
	if (hasKeepRotationReachedLimit()) {
		target = viewAngles;
	}
	calcRotation();
	DisabledRotation = ShouldDisabledRotation();
	if (DisabledRotation) { 
		current = viewAngles;
		return; 
	}
}
//CreateMove Update
void Helper::RotationManager::onCreateMove()
{
	
}

void Helper::RotationManager::setTargetRotation(Vector rotation, float keepLength)
{
	target = rotation;
	lastMS = I::GlobalVars->realtime;
	keepRotation = keepLength;
	DisabledRotation = false;
}

Vector Helper::RotationManager::getCurrentRotation()
{
	return current;
}
