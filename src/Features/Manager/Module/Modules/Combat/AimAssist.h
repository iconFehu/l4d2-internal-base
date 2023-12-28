#pragma once
#include "../../ModuleHeader.h"
namespace F {
	namespace AimAssistModule {
		class AimAssist : public Module
		{
		public:
			AimAssist() { this->Create("AimAssist", true, VK_NUMPAD1); };
			void onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onPostCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onRender2D() override;
			void onEnabled() override;
			void onDisabled() override;
		private:

		};
		inline AimAssist* Getinstance() {
			static AimAssist hop = AimAssist();
			return &hop;
		};
	};
};