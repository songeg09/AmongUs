#include "pch.h"
#include "Wall.h"
#include "WallDetector.h"
#include "SceneManager.h"
#include "GDIManager.h"
#include "Core.h"

Wall::Wall()
{

}

Wall::~Wall()
{

}

void Wall::Init(Vector2 _vec2Start, Vector2 _vec2End)
{
	m_vec2Start = _vec2Start;
	m_vec2End = _vec2End;
	m_vec2LineDir = m_vec2End - m_vec2Start;
	m_fLineLen = m_vec2LineDir.Length();
	m_vec2LineDir.Normalize();
	m_vec2WallNormal = { -m_vec2LineDir.m_fy, m_vec2LineDir.m_fx };
}

void Wall::ResolvePenetration(WallDetector* _other)
{
	Vector2 detectorPos = _other->GetPosition();
	Vector2 StartToDetector = detectorPos - m_vec2Start;

	float radius = _other->GetRadius();
	float t = Vector2::Dot(m_vec2LineDir, StartToDetector);
	t = std::clamp(t, 0.0f, m_fLineLen);

	Vector2 ClosestPoint = m_vec2Start + (m_vec2LineDir * t);
	float dist = (detectorPos - ClosestPoint).Length();

	if (dist < radius)
	{
		// 캐릭터 중심에서 벽의 시작점을 잇는 벡터
		Vector2 centerToLineStart = detectorPos - m_vec2Start;

		// 벽과 수직인 방향으로 튕겨나가는 양(침투 거리)
		float penetration = radius - dist;

		// 해당 디텍터를 가진 주인과 디텍터의 위치를 보정함
		Vector2 ResolveVec = m_vec2WallNormal * penetration;
		_other->ResolvePos(ResolveVec);
	}
}

void Wall::Render(HDC _memDC)
{
	if (Core::GetInstance()->IsShowCollider() == false)
		return;

	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);

	Vector2 BackBufferTopLeftInScene = SceneManager::GetInstance()->GetCurScene()->GetBackBufferTopLeftInScene();
	MoveToEx(_memDC, m_vec2Start.m_fx - BackBufferTopLeftInScene.m_fx, m_vec2Start.m_fy - BackBufferTopLeftInScene.m_fy, nullptr);
	LineTo(_memDC, m_vec2End.m_fx - BackBufferTopLeftInScene.m_fx, m_vec2End.m_fy - BackBufferTopLeftInScene.m_fy);

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}

