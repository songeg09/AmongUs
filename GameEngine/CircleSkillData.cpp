#include "pch.h"
#include "CircleSkillData.h"

void CircleSkillData::Load(std::wifstream& _loadFile)
{
	int tmp;
	_loadFile >> tmp;
	_loadFile >> SkillData::m_iZoneIndex;
	int UseTarget;
	_loadFile >> UseTarget;
	if (UseTarget == 1)
		SkillData::m_bUseTarget = true;
	else
		SkillData::m_bUseTarget = false;
}
