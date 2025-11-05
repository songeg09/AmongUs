#pragma once
#include "ZoneData.h"

class RectZoneData: public ZoneData
{
private:
	Vector2 m_vec2Size;
public:
	void Load(std::wifstream& _loadFile) override;
	Vector2 GetSize() { return m_vec2Size; }
};

