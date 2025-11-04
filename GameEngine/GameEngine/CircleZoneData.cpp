#include "pch.h"
#include "CircleZoneData.h"

void CircleZoneData::Load(std::wifstream& _loadFile)
{
	int tmp;
	_loadFile >> tmp;
	_loadFile >> m_fRadius;
	_loadFile >> ZoneData::m_iAnimationStart;
	_loadFile >> ZoneData::m_iAnimationEnd;
}
