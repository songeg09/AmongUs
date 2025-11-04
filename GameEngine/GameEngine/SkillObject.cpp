#include "pch.h"
#include "SkillObject.h"
#include "Collider.h"

SkillObject::SkillObject()
{
	m_pTarget = nullptr;
}

SkillObject::~SkillObject()
{
}

void SkillObject::Init(Object* _pTarget)
{
	m_pTarget = _pTarget;
}

void SkillObject::Update()
{
	if (m_pTarget != nullptr)
	{
		SetPosition(m_pTarget->GetPosition());
	}
}

void SkillObject::SetEnable(bool _bEnable)
{
	m_bEnable = _bEnable;
}
