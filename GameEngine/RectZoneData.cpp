#include "pch.h"
#include "RectZoneData.h"

void RectZoneData::Load(std::wifstream& _loadFile)
{
	int tmp;
	_loadFile >> tmp;
	_loadFile >> m_vec2Size.m_fx;
	_loadFile >> m_vec2Size.m_fy;
	_loadFile >> ZoneData::m_iAnimationStart;
	_loadFile >> ZoneData::m_iAnimationEnd;
}
