#include "EngineVGui.h"

#include "../../Features/Manager/Manager.h"

using namespace Hooks;

unsigned int __fastcall EngineVGui::GetPanel::Detour(void* ecx, void* edx, VGuiPanel_t type)
{
	return Table.Original<FN>(Index)(ecx, edx, type);
}

bool __fastcall EngineVGui::IsGameUIVisible::Detour(void* ecx, void* edx)
{
	return Table.Original<FN>(Index)(ecx, edx);
}

void __fastcall EngineVGui::ActivateGameUI::Detour(void* ecx, void* edx)
{
	Table.Original<FN>(Index)(ecx, edx);
}

void __fastcall EngineVGui::Paint::Detour(void* ecx, void* edx, int mode)
{
	Table.Original<FN>(Index)(ecx, edx, mode);
	if (!(mode & PAINT_UIPANELS))
		return;
	F::FeatureManager.onKey();

	if (!G::Draw.m_nScreenW)
		G::Draw.m_nScreenW = I::BaseClient->GetScreenWidth();

	if (!G::Draw.m_nScreenH)
		G::Draw.m_nScreenH = I::BaseClient->GetScreenHeight();

	I::MatSystemSurface->StartDrawing();
	{
		F::FeatureManager.onRender2D();
		G::Draw.String(EFonts::DEBUG, 5, 5, { 204, 204, 204, 255 }, TXT_DEFAULT, _(L"None - Left 4 dead 2 by Lak3(OC), crave#6948"));
	}
	I::MatSystemSurface->FinishDrawing();
}

void EngineVGui::Init()
{
	XASSERT(Table.Init(I::EngineVGui) == false);
	XASSERT(Table.Hook(&GetPanel::Detour, GetPanel::Index) == false);
	XASSERT(Table.Hook(&IsGameUIVisible::Detour, IsGameUIVisible::Index) == false);
	XASSERT(Table.Hook(&ActivateGameUI::Detour, ActivateGameUI::Index) == false);
	XASSERT(Table.Hook(&Paint::Detour, Paint::Index) == false);
}