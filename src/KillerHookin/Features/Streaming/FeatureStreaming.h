#pragma once

#include "Features/Base/FeatureBase.h"

class FeatureStreaming : public FeatureBase
{
public:
	FeatureStreaming() : FeatureBase() { }

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
