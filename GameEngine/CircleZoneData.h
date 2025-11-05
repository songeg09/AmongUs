#pragma once
#include "ZoneData.h"
class CircleZoneData : public ZoneData
{
private:
	float m_fRadius;
public:
	// Data을(를) 통해 상속됨
	void Load(std::wifstream& _loadFile) override;
	float GetRadius() { return m_fRadius; }
};

