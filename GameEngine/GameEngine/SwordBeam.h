#pragma once
#include "Skill.h"

class SwordBeamObject;
class SwordBeam : public Skill
{
private:
	SwordBeamObject* m_pSkillObject;

public:
	SwordBeam(int _iIndex, Actor* _pCaster, int _iKey);

	void Create() override;
	void Cast() override;
	void Fire() override;
};

