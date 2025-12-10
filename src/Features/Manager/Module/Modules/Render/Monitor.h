#pragma once
#include "../../ModuleHeader.h"

namespace F {
	namespace MonitorModule {
		class Monitor : public Module
		{
		public:
			Monitor() { this->Create("Monitor", true, VK_HOME); };
			void onRender2D() override;
		private:
			void DrawStatusPanel();
			void DrawHookStatus(int x, int y, int width);
			void DrawFeatureStatus(int x, int y, int width);
			void DrawGameInfo(int x, int y, int width);
			void DrawSystemInfo(int x, int y, int width);
		};
	};
};

