#include "pch.h"
#include "Wall.h"
#include "WallDetector.h"
#include "SceneManager.h"
#include "GDIManager.h"

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
	float radius = _other->GetRadius();

	//Vector2 MoveVec = _other->GetTarget()->GetMoveDirection();

	// 직선의 거리 계산
	float A = m_vec2End.m_fy - m_vec2Start.m_fy;
	float B = m_vec2Start.m_fx - m_vec2End.m_fx;
	float C = m_vec2End.m_fx * m_vec2Start.m_fy - m_vec2Start.m_fx * m_vec2End.m_fy;

	float dist = fabsf(A * detectorPos.m_fx + B * detectorPos.m_fy + C) / sqrtf(A * A + B * B);

	if (dist < radius)
	{
		// 캐릭터 중심에서 벽의 시작점을 잇는 벡터
		Vector2 centerToLineStart = detectorPos - m_vec2Start;

		// 캐릭터가 벽의 '안쪽'에 있는지 확인 (내적 사용)
		// 만약 wallNormal이 벽의 '바깥쪽'을 가리키지 않는다면 뒤집어 줍니다.
		// wallNormal과 centerToLineStart의 내적이 음수면, 
		// wallNormal이 캐릭터 중심을 향하고 있다는 뜻 (캐릭터가 벽의 안쪽에 있다는 가정)
		float dotProductWithNormal = Vector2::Dot(centerToLineStart, m_vec2WallNormal);

		// 만약 법선이 플레이어 중심 방향을 향하고 있다면 (벽의 바깥쪽을 향하지 않는다면), 뒤집는다.
		// 이렇게 해야 wallNormal이 항상 "플레이어를 벽 밖으로 밀어낼 방향"을 가리킵니다.
		//if (dotProductWithNormal < 0.0f)
		//{
		//	m_vec2WallNormal = m_vec2WallNormal * -1.0f;
		//}

		// 벽과 수직인 방향으로 튕겨나가는 양(침투 거리)
		float penetration = radius - dist;

		// 플레이어를 법선 방향으로 밀어냄 (이제 wallNormal은 항상 벽의 바깥쪽을 가리킵니다)
		Vector2 ResolveVec = m_vec2WallNormal * penetration;
		_other->ResolvePos(ResolveVec);


		//// 이동 방향을 슬라이딩 벡터로 보정
		//float Dot = Vector2::Dot(MoveVec, m_vec2WallNormal);
		//Vector2 slideVec = MoveVec - m_vec2WallNormal * Dot;

		//// 새 위치 적용
		//_other->GetTarget()->SetPosition(NewActorPos + slideVec * 0.1f);
		//_other->FinalUpdate();
	}
}

void Wall::Render(HDC _memDC)
{
	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);

	Vector2 BackBufferTopLeftInScene = SceneManager::GetInstance()->GetCurScene()->GetBackBufferTopLeftInScene();
	MoveToEx(_memDC, m_vec2Start.m_fx - BackBufferTopLeftInScene.m_fx, m_vec2Start.m_fy - BackBufferTopLeftInScene.m_fy, nullptr);
	LineTo(_memDC, m_vec2End.m_fx - BackBufferTopLeftInScene.m_fx, m_vec2End.m_fy - BackBufferTopLeftInScene.m_fy);

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}

