#pragma once
#include "../../SDK/SDK.h"
#include "../ESP/ESP.h"
#include "../EnginePrediction/EnginePrediction.h"
#include "vector"
#include "Module/Modules/Player/BunnyHop.h"
#include "Module/Modules/Render/Arraylist.h"
#include "Module/Modules/Render/ESPHelper.h"
#include "Module/Modules/Combat/Aimbot.h"
#include "Module/Modules/Combat/NoSpread.h"
namespace F {
	class Manager {

	public:
		std::vector<Module*> featurelist;
		BunnyHopModule::BunnyHop* bhop = &BunnyHopModule::BunnyHop();
		ArraylistModule::Arraylist* arraylist = &ArraylistModule::Arraylist();
		AimbotModule::Aimbot* aimbot = &AimbotModule::Aimbot();
		NoSpreadModule::NoSpread* noSpread = &NoSpreadModule::NoSpread();
		ESPHelperModule::ESPHelper* espHelper = &ESPHelperModule::ESPHelper();
		void Init();
		void onRender2D();
		void onCreateMove(CUserCmd* cmd, C_TerrorPlayer* pLocal);
		void onKey();
	};
	inline Manager FeatureManager; 
}