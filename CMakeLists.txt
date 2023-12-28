cmake_minimum_required(VERSION 3.12)
project(l4d2_base)  # Replace l4d2_base with the actual project name

# Collect source files
set(SOURCE_FILES
    src/DllMain.cpp
    src/Util/Util.cpp
    src/Util/Pattern/Pattern.cpp
    src/Util/Offsets/Offsets.cpp
    src/Util/VFunc/VFunc.cpp
    src/Util/Math/Math.cpp
    src/Util/NetVarManager/NetVarManager.cpp
    src/Util/Hook/MinHook/buffer.c
    src/Util/Hook/MinHook/hook.c
    src/Util/Hook/MinHook/trampoline.c
    src/Util/Hook/MinHook/hde/hde32.c
    src/Util/Hook/MinHook/hde/hde64.c
    src/Util/Interface/Interface.cpp
    src/SDK/L4D2/Includes/checksum_md5.cpp
    src/SDK/L4D2/Includes/basehandle.cpp
    src/SDK/KeyValues/KeyValues.cpp
    src/SDK/GameUtil/GameUtil.cpp
    src/SDK/DrawManager/DrawManager.cpp
    src/SDK/SDK.cpp
    src/Entry/Entry.cpp
    src/Features/ESP/ESP.cpp
    src/Hooks/Hooks.cpp
    src/Hooks/TerrorPlayer/TerrorPlayer.cpp
    src/Hooks/ClientMode/ClientMode.cpp
    src/Hooks/ClientPrediction/ClientPrediction.cpp
    src/Hooks/CL_Main/CL_Main.cpp
    src/Hooks/BasePlayer/BasePlayer.cpp
    src/Hooks/BaseClient/BaseClient.cpp
    src/Hooks/EngineVGui/EngineVGui.cpp
    src/Hooks/WndProc/WndProc.cpp
    src/Features/Vars.cpp
    src/Features/Manager/Module/Modules/Combat/NoSpread.cpp
    src/Hooks/SequenceTransitioner/SequenceTransitioner.cpp
    src/Hooks/ModelRender/ModelRender.cpp
    src/Hooks/ModelRenderSystem/ModelRenderSystem.cpp
    src/Hooks/TerrorGameRules/TerrorGameRules.cpp
    src/Features/EnginePrediction/EnginePrediction.cpp
    src/Features/Manager/Manager.cpp
    src/Features/Manager/Module/Modules/Player/BunnyHop.cpp
    src/Features/Manager/Module/Modules/Render/Arraylist.cpp
    src/Features/Manager/Module/Modules/Combat/Aimbot.cpp
    src/Features/Manager/RotationManager.cpp
    src/Features/Manager/Module/Modules/Combat/AimAssist.cpp
    src/Features/Manager/Module/Utils/FindTarget.cpp
    src/Features/Manager/Module/Modules/Render/ESPHelper.cpp
)

# Collect header files
set(HEADER_FILES
    src/Util/Util.h
    src/Util/Pattern/Pattern.h
    src/Util/Offsets/Offsets.h
    src/Util/VFunc/VFunc.h
    src/Util/Math/Vector/Vector.h
    src/Util/Math/Vector/Vector2D.h
    src/Util/Math/Math.h
    src/Util/NetVarManager/NetVarManager.h
    src/Util/Hook/Hook.h
    src/Util/Hook/MinHook/buffer.h
    src/Util/Hook/MinHook/MinHook.h
    src/Util/Hook/MinHook/trampoline.h
    src/Util/Hook/MinHook/hde/hde32.h
    src/Util/Hook/MinHook/hde/hde64.h
    src/Util/Hook/MinHook/hde/pstdint.h
    src/Util/Hook/MinHook/hde/table32.h
    src/Util/Hook/MinHook/hde/table64.h
    src/Util/Interface/Interface.h
    src/SDK/L4D2/Includes/usercmd.h
    src/SDK/L4D2/Includes/globalvars_base.h
    src/SDK/L4D2/Includes/dt_common.h
    src/SDK/L4D2/Includes/dt_recv.h
    src/SDK/L4D2/Includes/client_class.h
    src/SDK/L4D2/Includes/color.h
    src/SDK/L4D2/Includes/const.h
    src/SDK/L4D2/Includes/appsystem.h
    src/SDK/L4D2/Includes/checksum_md5.h
    src/SDK/L4D2/Includes/basehandle.h
    src/SDK/L4D2/Includes/ehandle.h
    src/SDK/L4D2/Interfaces/BaseClientDLL.h
    src/SDK/L4D2/Interfaces/DebugOverlay.h
    src/SDK/L4D2/Interfaces/ClientEntityList.h
    src/SDK/L4D2/Interfaces/EngineClient.h
    src/SDK/L4D2/Interfaces/EngineTrace.h
    src/SDK/L4D2/Interfaces/EngineVGui.h
    src/SDK/L4D2/Interfaces/GameMovement.h
    src/SDK/L4D2/Interfaces/ModelInfo.h
    src/SDK/L4D2/Interfaces/ModelRender.h
    src/SDK/L4D2/Interfaces/MoveHelper.h
    src/SDK/L4D2/Interfaces/Prediction.h
    src/SDK/L4D2/Interfaces/RenderView.h
    src/SDK/L4D2/Interfaces/VGuiPanel.h
    src/SDK/L4D2/Interfaces/VGuiSurface.h
    src/SDK/L4D2/Interfaces/MatSystemSurface.h
    src/SDK/L4D2/Interfaces/MatRenderContext.h
    src/SDK/L4D2/Interfaces/MaterialSystem.h
    src/SDK/L4D2/Entities/IHandleEntity.h
    src/SDK/L4D2/Entities/IClientUnknown.h
    src/SDK/L4D2/Entities/IClientThinkable.h
    src/SDK/L4D2/Entities/IClientRenderable.h
    src/SDK/L4D2/Entities/IClientNetworkable.h
    src/SDK/L4D2/Entities/IClientEntity.h
    src/SDK/KeyValues/KeyValues.h
    src/SDK/GameUtil/GameUtil.h
    src/SDK/DrawManager/DrawManager.h
    src/SDK/SDK.h
    src/Entry/Entry.h
    src/Features/Vars.h
    src/Features/ESP/ESP.h
    src/Hooks/Hooks.h
    src/Hooks/TerrorPlayer/TerrorPlayer.h
    src/Hooks/ClientMode/ClientMode.h
    src/Hooks/ClientPrediction/ClientPrediction.h
    src/Hooks/CL_Main/CL_Main.h
    src/Hooks/BasePlayer/BasePlayer.h
    src/Hooks/BaseClient/BaseClient.h
    src/Hooks/EngineVGui/EngineVGui.h
    src/SDK/L4D2/Entities/C_BaseEntity.h
    src/SDK/L4D2/Entities/C_BaseAnimating.h
    src/SDK/L4D2/Entities/C_BasePlayer.h
    src/SDK/L4D2/Entities/C_DynamicProp.h
    src/SDK/L4D2/Entities/C_WeaponCSBase.h
    src/SDK/L4D2/Entities/C_TerrorWeapon.h
    src/SDK/L4D2/Entities/C_CSPlayer.h
    src/SDK/L4D2/Entities/C_TerrorPlayer.h
    src/SDK/L4D2/Entities/C_Infected.h
    src/Hooks/WndProc/WndProc.h
    src/Hooks/SequenceTransitioner/SequenceTransitioner.h
    src/Hooks/ModelRender/ModelRender.h
    src/Hooks/ModelRenderSystem/ModelRenderSystem.h
    src/Hooks/TerrorGameRules/TerrorGameRules.h
    src/Util/XorString/XorString.h
    src/Features/EnginePrediction/EnginePrediction.h
    src/Features/Manager/Manager.h
    src/Features/Manager/Module/ModuleHeader.h
    src/Features/Manager/Module/Modules/Player/BunnyHop.h
    src/Features/Manager/Module/Modules/Render/Arraylist.h
    src/Features/Manager/Module/Modules/Combat/Aimbot.h
    src/Features/Manager/RotationManager.h
    src/Features/Manager/Module/Modules/Combat/AimAssist.h
    src/Features/Manager/Module/Utils/FindTarget.h
    src/Features/Manager/Module/Utils/UtilsCollector.h
    src/Features/Manager/Module/Modules/Render/ESPHelper.h
    src/SDK/L4D2/Includes/view_shared.h
)

# Add the executable target
add_executable(l4d2_base ${SOURCE_FILES} ${HEADER_FILES})

# Set C++ standard
set_target_properties(l4d2_base PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Include directories
target_include_directories(l4d2_base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    # Add any additional include directories here
)

# Set compile options based on build configurations
target_compile_options(l4d2_base PRIVATE
    "$<$<CONFIG:Debug>: /Od /MDd /Zi /RTC1 /EHsc>"
    "$<$<CONFIG:Release>: /O2 /MD /EHsc>"
)

# Set additional compile definitions
target_compile_definitions(l4d2_base PRIVATE
    "$<$<CONFIG:Debug>: _DEBUG;_CONSOLE>"
    "$<$<CONFIG:Release>: NDEBUG;_CONSOLE>"
)

# Set link options based on build configurations
target_link_options(l4d2_base PRIVATE
    "$<$<CONFIG:Debug>: /DEBUG>"
    "$<$<CONFIG:Release>: /INCREMENTAL:NO /OPT:REF /OPT:ICF>"
)
