#pragma once

#include "../Hooks/Hooks.h"

class CGlobal_ModuleEntry
{
public:
	void Load();
	void Unload();
	bool ShouldUnload();
};

namespace G { inline CGlobal_ModuleEntry ModuleEntry; }