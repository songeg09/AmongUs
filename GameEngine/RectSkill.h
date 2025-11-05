#pragma once
#include "Skill.h"

class RectZone;
class RectSkill : public Skill
{
protected:
	RectZone* m_pSkillObject;
public:
	RectSkill(int _iIndex, Actor* _pCaster, int _iKey);

	void Create() override;
};
