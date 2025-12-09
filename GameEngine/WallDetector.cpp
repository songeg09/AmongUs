#include "pch.h"
#include "WallDetector.h"+		std::enable_shared_from_this<Object>	{_Wptr={...} }	std::enable_shared_from_this<Object>

#include "Object.h"
#include "SceneManager.h"
#include "GDIManager.h"
#include "Core.h"

WallDetector::WallDetector()
{
}

WallDetector::~WallDetector()
{
}

void WallDetector::Init(std::shared_ptr<Object> _pOwner, Vector2 _vec2Offset, float _fRadius)
{
	m_pOwner = _pOwner;
	m_vec2Offset = _vec2Offset;
	m_vec2Position = m_pOwner.lock()->GetPosition();
	m_vec2Position += m_vec2Offset;
	m_fRadius = _fRadius;
}

void WallDetector::Update()
{
	m_vec2Position = m_pOwner.lock()->GetPosition() + m_vec2Offset;
}

void WallDetector::Render(HDC _memDC)
{
	if (Core::GetInstance()->IsShowCollider() == false)
		return;

	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);

	Vector2 BackBufferTopLeftInScene = SceneManager::GetInstance()->GetCurScene()->GetBackBufferTopLeftInScene();
	Vector2 PosOnBackBuffer = m_vec2Position - BackBufferTopLeftInScene;
	Ellipse(_memDC,
		PosOnBackBuffer.m_fx - m_fRadius, PosOnBackBuffer.m_fy - m_fRadius,
		PosOnBackBuffer.m_fx + m_fRadius, PosOnBackBuffer.m_fy + m_fRadius
	);

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}

void WallDetector::ResolvePos(Vector2 _vec2ResolveVec)
{
	m_pOwner.lock()->AddPosition(_vec2ResolveVec);
	m_vec2Position = m_vec2Position + _vec2ResolveVec;
}
