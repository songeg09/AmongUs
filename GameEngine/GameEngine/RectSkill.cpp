#include "pch.h"
#include "RectSkill.h"
#include "RectZone.h"
#include "RectSkillData.h"
#include "ResourceManager.h"
#include "TimerManager.h"
#include "Actor.h"
#include "SceneManager.h"
#include "InputManager.h"

RectSkill::RectSkill(int _iIndex, Actor* _pCaster, int _iKey)
	: Skill(_iIndex, _pCaster, _iKey)
{
	m_pSkillObject = nullptr;
}

void RectSkill::Create()
{
	RectSkillData* data = static_cast<RectSkillData*>(ResourceManager::GetInstance()->GetData(L"RectSkill.txt", Skill::GetIndex()));
	if (data != nullptr)
	{
		if (m_pSkillObject == nullptr)
		{
			m_pSkillObject = new RectZone;
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
