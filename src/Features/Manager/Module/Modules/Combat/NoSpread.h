#pragma once
#include "../../ModuleHeader.h"

namespace F {
	namespace NoSpreadModule {
		class NoSpread : public Module
		{
		public:
			NoSpread() { this->Create("NoSpread", true, VK_NUMPAD8); };
			void onPreCreateMove(CUserCmd* cmd,C_TerrorWeapon* pWeapon, C_TerrorPlayer* pLocal) override;
		private:

		};
		inline NoSpread* Getinstance() {
			static NoSpread hop = NoSpread();
			return &hop;
		};
	};
};