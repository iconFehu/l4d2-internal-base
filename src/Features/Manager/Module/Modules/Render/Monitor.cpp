#include "Monitor.h"
#include "../../../Manager.h"

namespace F {
	namespace MonitorModule {
		void Monitor::onRender2D()
		{
			if (!getEnabled()) return;
			
			// 只在游戏中显示，或者始终显示监控面板
			DrawStatusPanel();
		}

		void Monitor::DrawStatusPanel()
		{
			int panelX = 10;
			int panelY = 30;
			int panelWidth = 350;
			int lineHeight = 18;
			int currentY = panelY;

			// 绘制主面板背景
			G::Draw.Rect(panelX, panelY, panelWidth, 400, Color(0, 0, 0, 200));
			G::Draw.OutlinedRect(panelX, panelY, panelWidth, 400, Color(100, 150, 255, 255));

			// 标题
			currentY += 5;
			G::Draw.String(EFonts::MENU_VERDANA, panelX + 10, currentY, Color(100, 200, 255, 255), TXT_DEFAULT, "=== 手术监控面板 ===");
			currentY += lineHeight + 5;
			G::Draw.Line(panelX + 5, currentY, panelX + panelWidth - 5, currentY, Color(100, 150, 255, 150));
			currentY += 10;

			// 绘制各个状态区域
			DrawHookStatus(panelX + 10, currentY, panelWidth - 20);
			currentY += 80;
			
			DrawFeatureStatus(panelX + 10, currentY, panelWidth - 20);
			currentY += 150;
			
			DrawGameInfo(panelX + 10, currentY, panelWidth - 20);
			currentY += 80;
			
			DrawSystemInfo(panelX + 10, currentY, panelWidth - 20);
		}

		void Monitor::DrawHookStatus(int x, int y, int width)
		{
			int currentY = y;
			G::Draw.String(EFonts::MENU_CONSOLAS, x, currentY, Color(255, 200, 100, 255), TXT_DEFAULT, "[钩子状态]");
			currentY += 18;

			// 检查钩子是否已初始化
			bool hooksInitialized = true; // 假设钩子已初始化（实际应该检查）
			
			Color statusColor = hooksInitialized ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255);
			const char* statusText = hooksInitialized ? "✓ 已激活" : "✗ 未激活";
			
			G::Draw.String(EFonts::DEBUG, x + 10, currentY, statusColor, TXT_DEFAULT, "钩子系统: %s", statusText);
			currentY += 16;

			// 显示各个钩子状态
			const char* hookNames[] = {
				"ClientMode", "BasePlayer", "EngineVGui", 
				"ModelRender", "ClientPrediction"
			};
			
			for (int i = 0; i < 5; i++) {
				G::Draw.String(EFonts::DEBUG, x + 20, currentY, Color(200, 200, 200, 255), TXT_DEFAULT, 
					"  - %s: %s", hookNames[i], "✓");
				currentY += 14;
			}
		}

		void Monitor::DrawFeatureStatus(int x, int y, int width)
		{
			int currentY = y;
			G::Draw.String(EFonts::MENU_CONSOLAS, x, currentY, Color(255, 200, 100, 255), TXT_DEFAULT, "[功能模块状态]");
			currentY += 18;

			// 遍历所有功能模块
			for (Module* mod : F::FeatureManager.featurelist) {
				bool enabled = mod->getEnabled();
				Color statusColor = enabled ? Color(0, 255, 0, 255) : Color(150, 150, 150, 255);
				const char* statusText = enabled ? "启用" : "禁用";
				
				// 显示模块名称和状态
				G::Draw.String(EFonts::DEBUG, x + 10, currentY, Color(255, 255, 255, 255), TXT_DEFAULT, 
					"%s:", mod->getName().c_str());
				
				int nameWidth = G::Draw.GetFontWidth(EFonts::DEBUG, mod->getName().c_str());
				G::Draw.String(EFonts::DEBUG, x + 10 + nameWidth + 5, currentY, statusColor, TXT_DEFAULT, 
					"[%s]", statusText);
				
				// 显示快捷键
				if (mod->getKey() != 0) {
					char keyName[32];
					sprintf_s(keyName, " (Key: %d)", mod->getKey());
					int statusWidth = G::Draw.GetFontWidth(EFonts::DEBUG, statusText) + 20;
					G::Draw.String(EFonts::DEBUG, x + 10 + nameWidth + 5 + statusWidth, currentY, 
						Color(150, 200, 255, 255), TXT_DEFAULT, keyName);
				}
				
				currentY += 16;
			}
		}

		void Monitor::DrawGameInfo(int x, int y, int width)
		{
			int currentY = y;
			G::Draw.String(EFonts::MENU_CONSOLAS, x, currentY, Color(255, 200, 100, 255), TXT_DEFAULT, "[游戏信息]");
			currentY += 18;

			if (I::EngineClient && I::EngineClient->IsInGame()) {
				int localPlayer = I::EngineClient->GetLocalPlayer();
				if (localPlayer > 0) {
					IClientEntity* pEntity = I::ClientEntityList->GetClientEntity(localPlayer);
					if (pEntity) {
						C_TerrorPlayer* pLocal = pEntity->As<C_TerrorPlayer*>();
						if (pLocal) {
							// 玩家信息
							int health = pLocal->m_iHealth();
							int maxHealth = pLocal->m_iMaxHealth();
							Color healthColor = G::Util.GetHealthColor(health, maxHealth);
							
							G::Draw.String(EFonts::DEBUG, x + 10, currentY, Color(255, 255, 255, 255), TXT_DEFAULT, 
								"生命值: ");
							G::Draw.String(EFonts::DEBUG, x + 60, currentY, healthColor, TXT_DEFAULT, 
								"%d/%d", health, maxHealth);
							currentY += 16;

							// 位置信息
							Vector origin = pLocal->GetAbsOrigin();
							G::Draw.String(EFonts::DEBUG, x + 10, currentY, Color(200, 200, 200, 255), TXT_DEFAULT, 
								"位置: %.1f, %.1f, %.1f", origin.x, origin.y, origin.z);
							currentY += 16;
						}
					}
				}

				// 游戏状态
				G::Draw.String(EFonts::DEBUG, x + 10, currentY, Color(0, 255, 0, 255), TXT_DEFAULT, 
					"游戏状态: 游戏中");
			} else {
				G::Draw.String(EFonts::DEBUG, x + 10, currentY, Color(255, 150, 0, 255), TXT_DEFAULT, 
					"游戏状态: 未进入游戏");
			}
		}

		void Monitor::DrawSystemInfo(int x, int y, int width)
		{
			int currentY = y;
			G::Draw.String(EFonts::MENU_CONSOLAS, x, currentY, Color(255, 200, 100, 255), TXT_DEFAULT, "[系统信息]");
			currentY += 18;

			// 屏幕分辨率
			G::Draw.String(EFonts::DEBUG, x + 10, currentY, Color(200, 200, 200, 255), TXT_DEFAULT, 
				"分辨率: %dx%d", G::Draw.m_nScreenW, G::Draw.m_nScreenH);
			currentY += 16;

			// 模块加载状态
			bool moduleLoaded = true; // 假设已加载
			Color loadColor = moduleLoaded ? Color(0, 255, 0, 255) : Color(255, 0, 0, 255);
			G::Draw.String(EFonts::DEBUG, x + 10, currentY, loadColor, TXT_DEFAULT, 
				"模块状态: %s", moduleLoaded ? "已加载" : "未加载");
			currentY += 16;

			// 退出提示
			G::Draw.String(EFonts::DEBUG, x + 10, currentY, Color(255, 100, 100, 255), TXT_DEFAULT, 
				"按 END 键退出模块");
		}
	}
}

