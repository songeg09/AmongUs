#pragma once

class CircleZone;
class CircleDamageSkill : public Skill
{
private:
	CircleZone* m_pSkillObject;
public:
	CircleDamageSkill(int _iIndex, Actor* _pCaster, int _iKey);

	void Create() override;
	void Cast() override;
	void Fire() override;
};
