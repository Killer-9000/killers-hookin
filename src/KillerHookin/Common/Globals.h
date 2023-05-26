#pragma once

#include "Features/Base/FeatureBase.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <memory>
#include <stdint.h>
#include <vector>

namespace Globals
{
	static size_t g_baseAddress = 0;
	static HMODULE g_module = nullptr;
	static bool g_running = false;
	static bool g_menuShown = false;

	static std::vector<std::unique_ptr<FeatureBase>> g_features;
}
