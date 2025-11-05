#pragma once
#include "Data.h"
class SkillData : public Data
{
protected:
	int m_iZoneIndex;
	bool m_bUseTarget;

public:
	virtual void Load(std::wifstream& _loadFile) = 0;
	int GetZoneIndex() { return m_iZoneIndex; }
	bool GetUseTarget() { return m_bUseTarget; }
};

