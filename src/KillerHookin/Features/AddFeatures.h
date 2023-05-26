#pragma once

#include "Common/Globals.h"

#include "Hotfixes/FeatureHotfixes.h"
#include "MapLiveView/FeatureMapLiveView.h"
#include "MapPhasing/FeatureMapPhasing.h"
#include "Rendering/FeatureRendering.h"
#include "Streaming/FeatureStreaming.h"

namespace Features
{
	void InitializeFeatures()
	{
		for (int i = 0; i < Globals::g_features.size(); i++)
			if (!Globals::g_features[i]->Initialize())
				Globals::g_features.erase(Globals::g_features.begin() + i);
		Globals::g_features.shrink_to_fit();
	}

	void DeinitializeFeatures()
	{
		for (auto& feature : Globals::g_features)
			feature->Deinitialize();
		Globals::g_features.clear();
	}

	void UpdateFeatures(uint32_t delta)
	{
		for (auto& feature : Globals::g_features)
			feature->Update(delta);
	}

	void AddFeatures()
	{
		if (Globals::g_features.size())
			DeinitializeFeatures();
		else
			Globals::g_features.reserve(8);

		Globals::g_features.emplace_back(new FeatureHotfixes());
		Globals::g_features.emplace_back(new FeatureMapLiveView());
		Globals::g_features.emplace_back(new FeatureMapPhasing());
		Globals::g_features.emplace_back(new FeatureRendering());
		Globals::g_features.emplace_back(new FeatureStreaming());
		
	}
}