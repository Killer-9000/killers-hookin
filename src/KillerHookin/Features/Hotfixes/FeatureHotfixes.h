#pragma once

#include "Features/Base/FeatureBase.h"

class FeatureHotfixes : public FeatureBase
{
public:
	FeatureHotfixes() : FeatureBase() { }

	virtual bool Initialize() override
	{

		m_initialized = true;
		return true;
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
