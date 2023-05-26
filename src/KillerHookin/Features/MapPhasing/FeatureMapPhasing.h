#pragma once

#include "Features/Base/FeatureBase.h"

/*
G_MapDBCStore usage locations
{
	004057a5
}

007bfce0  void __cdecl CMap_Load(char *mapName,uint32_t mapID)

const char* dbcName = "DBFilesClient\\MapExt.dbc";

void Hook(char* mapName, uint32_t mapID)
{
	// Load normally.
	CMap_Load(mapName, mapID);

	// Load base map.
	int32_t parentID = _MapExtStore.Get(mapID);
	if (parentID == -1)
		return;

	// If a tile doesn't exist in base version, load it.
}

*/

class FeatureMapPhasing : public FeatureBase
{
public:
	FeatureMapPhasing() : FeatureBase() { }

	virtual bool Initialize() override
	{

		m_initialized = true;
		return false;
	}

	virtual bool Deinitialize() override
	{
		m_initialized = false;

		return true;
	}

	virtual void Update(uint32_t delta) override
	{

	}
};
