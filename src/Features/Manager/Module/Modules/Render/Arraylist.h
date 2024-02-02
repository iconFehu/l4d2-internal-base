#pragma once
#include "../../ModuleHeader.h"

namespace F {
	namespace ArraylistModule {
		class Arraylist : public Module
		{
		public:
			Arraylist() { this->Create("ArrayList", true, VK_NUMPAD0); };
			void onRender2D() override;
		private:

		};
	};
};