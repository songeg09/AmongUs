#pragma once
#include "SkillData.h"
class CircleSkillData : public SkillData
{
public:
	// Data을(를) 통해 상속됨
	void Load(std::wifstream& _loadFile) override;
};

