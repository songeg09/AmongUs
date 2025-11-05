#include "pch.h"
#include "Skill.h"
#include "CircleDamageSkill.h"
#include "CircleSkillData.h"
#include "CircleZone.h"
#include "ResourceManager.h"
#include "Actor.h"
#include "SceneManager.h"
#include "InputManager.h"

CircleDamageSkill::CircleDamageSkill(int _iIndex, Actor* _pCaster, int _iKey)
	: Skill(_iIndex, _pCaster, _iKey)
{
	m_pSkillObject = nullptr;
}

void CircleDamageSkill::Create()
{
	CircleSkillData* data = static_cast<CircleSkillData*>(ResourceManager::GetInstance()->GetData(L"CircleSkill.txt", Skill::GetIndex()));
	if (data != nullptr)
	{
		if (m_pSkillObject == nullptr)
		{
			m_pSkillObject = new CircleZone;
			SceneManager::GetInstance()->GetCurScene()->AddObject(m_pSkillObject, Skill::GetObjectGroup());
		}

		if (data->GetUseTarget() == true)
			m_pSkillObject->Init(data->GetZoneIndex(), Skill::GetCaster());
		else
		{

			m_pSkillObject->Init(data->GetZoneIndex());
			m_pSkillObject->SetPosition(Skill::GetCaster()->GetPosition());
		}
	}
}

void CircleDamageSkill::Cast()
{
	const std::list<Actor*>& targetList = m_pSkillObject->GetTargetList();
	for (Actor* actor : targetList)
	{
		Vector2 ForceDirection = m_pSkillObject->GetPosition() - actor->GetPosition();
		if (ForceDirection.Length() >= 30.0f)
		{
			ForceDirection.Normalize();
			actor->SetVelocity(ForceDirection * 30.0f);
		}
		else
			actor->SetVelocity({ 0.0f,0.0f });
	}
}

void CircleDamageSkill::Fire()
{
	const std::list<Actor*>& targetList = m_pSkillObject->GetTargetList();
	for (Actor* actor : targetList)
	{
		Vector2 ForceDirection = actor->GetPosition() - m_pSkillObject->GetPosition();
		ForceDirection.Normalize();
		actor->AddForce(ForceDirection * 500.0f);
	}
	m_pSkillObject->SetEnable(false);
}