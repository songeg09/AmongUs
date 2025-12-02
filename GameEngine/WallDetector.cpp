#include "pch.h"
#include "WallDetector.h"
#include "Object.h"
#include "SceneManager.h"
#include "GDIManager.h"

void WallDetector::Init(Object* _pOwner, Vector2 _vec2Offset, float _fRadius)
{
	m_pOwner = _pOwner;
	m_vec2Offset = _vec2Offset;
	m_vec2Position = m_pOwner->GetPosition();
	m_vec2Position += m_vec2Offset;
	m_fRadius = _fRadius;
}

void WallDetector::Update()
{
	m_vec2Position = m_pOwner->GetPosition() + m_vec2Offset;
}

void WallDetector::Render(HDC _memDC)
{
	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);

	Vector2 BackBufferTopLeftInScene = SceneManager::GetInstance()->GetCurScene()->GetBackBufferTopLeftInScene();
	Vector2 PosOnBackBuffer = m_vec2Position - BackBufferTopLeftInScene;
	Ellipse(_memDC, 
		PosOnBackBuffer.m_fx - m_fRadius / 2.0f, PosOnBackBuffer.m_fy - m_fRadius / 2.0f,
		PosOnBackBuffer.m_fx + m_fRadius / 2.0f, PosOnBackBuffer.m_fy + m_fRadius / 2.0f
	);

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}



void WallDetector::ResolvePos(Vector2 _vec2ResolveVec)
{
	m_pOwner->AddPosition(_vec2ResolveVec);
	m_vec2Position = m_vec2Position + _vec2ResolveVec;
}
