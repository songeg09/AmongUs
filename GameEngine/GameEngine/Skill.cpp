#include "pch.h"
#include "Skill.h"
#include "ResourceManager.h"

#include "Actor.h"
#include "SceneManager.h"
#include "InputManager.h"

Skill::Skill(int _iIndex, Actor* _pCaster, int _iKey)
{
	m_iKey = _iKey;
	InputManager::GetInstance()->RegistKey(m_iKey);
	m_iIndex = _iIndex;
	m_pCaster = _pCaster;
	if (m_pCaster->GetActorType() == ACTOR_TYPE::PLAYER)
		m_eSkillGroup = OBJECT_GROUP::PLAYER_SKILL;
	else if (m_pCaster->GetActorType() == ACTOR_TYPE::MONSTER)
		m_eSkillGroup = OBJECT_GROUP::MONSTER_SKILL;
}

void Skill::Input()
{
	switch (InputManager::GetInstance()->GetKeyState(m_iKey))
	{
	case KEY_STATE::DOWN:
		Create();
		break;
	case KEY_STATE::PRESS:
		Cast();
		break;
	case KEY_STATE::UP:
		Fire();
		break;
	}
}
