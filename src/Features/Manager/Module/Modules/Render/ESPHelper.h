#pragma once
#include "../../ModuleHeader.h"

namespace F {
	namespace ESPHelperModule {
		class ESPHelper : public Module
		{
		public:
			ESPHelper() { this->Create("ESPHelper", true, VK_RIGHT); };
			void onRender2D() override;
		private:

		};
		inline ESPHelper* Getinstance() {
			static ESPHelper arraylist = ESPHelper();
			return &arraylist;
		};
	};
};