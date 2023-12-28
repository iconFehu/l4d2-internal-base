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
#include "Module/Modules/Combat/AimAssist.h"
class Manager {

public:
	std::vector<Module*> featurelist;
	void Init();
	void onRender2D();
	void onCreateMove(CUserCmd* cmd, C_TerrorPlayer* pLocal);
	void onKey();
};
namespace F { inline Manager FeatureManager; }