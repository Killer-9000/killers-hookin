#pragma once

#include <cstdint>
#include <stdint.h>

class FeatureBase
{
public:
	virtual bool Initialize() = 0;
	virtual bool Deinitialize() = 0;

	virtual void Update(uint32_t delta) = 0;

	bool IsInitialized() const { return m_initialized; }

protected:
	bool m_initialized = false;
};
