#pragma once
#include "../../SDK/SDK.h"
namespace Helper
{
	class RotationManager
	{
	public:
		Vector current = Vector(), target = Vector();
		float keepRotation = 0;
		float acceletion = 0;
		float lastMS = 0;
		bool DisabledRotation = false;
		bool ShouldDisabledRotation();
		void calcRotation();
		void onUpdate();
		void onCreateMove();
		void setTargetRotation(Vector rotation, float keepLength);
		Vector getCurrentRotation();
	private:
		bool hasKeepRotationReachedLimit();
	};
	inline RotationManager rotationManager = RotationManager();
}