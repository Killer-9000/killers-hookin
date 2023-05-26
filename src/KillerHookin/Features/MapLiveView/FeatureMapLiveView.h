#pragma once

#include "Features/Base/FeatureBase.h"

class FeatureMapLiveView : public FeatureBase
{
public:
	FeatureMapLiveView() : FeatureBase() { }

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
