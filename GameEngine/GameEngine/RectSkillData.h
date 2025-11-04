#pragma once
#include "SkillData.h"
class RectSkillData : public SkillData
{
public:
	void Load(std::wifstream& _loadFile) override;
};

