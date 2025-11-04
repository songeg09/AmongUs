#pragma once
#include "Data.h"

class ZoneData : public Data
{
protected:
	int m_iAnimationStart;
	int m_iAnimationEnd;

public:
	virtual void Load(std::wifstream& _loadFile) = 0;
	int GetAnimationStart() { return m_iAnimationStart; }
	int GetAnimationEnd() { return m_iAnimationEnd; }
};

