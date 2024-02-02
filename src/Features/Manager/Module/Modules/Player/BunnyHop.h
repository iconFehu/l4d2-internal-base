#pragma once
#include "../../ModuleHeader.h"

namespace F {
	namespace BunnyHopModule {
		class BunnyHop : public Module
		{
		public:
			BunnyHop() { this->Create("Bhop", true, VK_NUMPAD9); };
			void onPreCreateMove(CUserCmd* cmd, C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
			void onRender2D() override;
		private:

		};
	};
};