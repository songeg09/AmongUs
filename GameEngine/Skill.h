#pragma once
#include "Animation.h"
class Actor;
class Skill abstract
{
private:
	Actor* m_pCaster;
	int m_iIndex;
	OBJECT_GROUP m_eSkillGroup;
	int m_iKey;

public:
	Skill(int _iIndex, Actor* _pCaster, int _iKey);
	void Input();
	Actor* GetCaster() { return m_pCaster; }
	int GetIndex() { return m_iIndex; }
	OBJECT_GROUP GetObjectGroup() { return m_eSkillGroup; }
	virtual void Create() = 0;
	virtual void Cast() = 0;
	virtual void Fire() = 0;
};





