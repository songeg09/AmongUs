#include "pch.h"
#include "SwordBeam.h"
#include "SwordBeamObject.h"
#include "SceneManager.h"
#include "RectSkillData.h"
#include "Actor.h"
#include "Player.h"

SwordBeam::SwordBeam(int _iIndex, Actor* _pCaster, int _iKey)
	:Skill(_iIndex, _pCaster, _iKey)
{
	m_pSkillObject = nullptr;
}

void SwordBeam::Create()
{
	RectSkillData* data = static_cast<RectSkillData*>(ResourceManager::GetInstance()->GetData(L"RectSkill.txt", Skill::GetIndex()));
	if (data != nullptr)
	{
		if (m_pSkillObject == nullptr)
		{
			m_pSkillObject = new SwordBeamObject;
			SceneManager::GetInstance()->GetCurScene()->AddObject(m_pSkillObject, Skill::GetObjectGroup());
		}
		
		if (m_pSkillObject->GetEnbale() == true)
			return;

		m_pSkillObject->Init(
			data->GetZoneIndex(), 
			Skill::GetCaster()->GetDirection(),
			Skill::GetCaster()->GetPosition(),
			500.f,
			500.f
		);
		m_pSkillObject->SetPosition(Skill::GetCaster()->GetPosition());
		static_cast<Player*>(Skill::GetCaster())->SetInput(false);
		Skill::GetCaster()->SetAnimation(Player::ANIMATION::ATTACK);
	}
}

void SwordBeam::Cast()
{
}

void SwordBeam::Fire()
{
}
