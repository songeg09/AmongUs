#include "pch.h"
#include "Wall.h"
#include "Collider.h"

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
	m_vec2Normal = m_vec2End - m_vec2Start;
	m_fLineLen = m_vec2Normal.Length();
	m_vec2Normal.Normalize();
	m_vec2WallNormal = { -m_vec2Normal.m_fy, m_vec2Normal.m_fx };

	Collider* wall = CreateLineCollider(COLLISION_TAG::WALL, true, m_vec2Start, m_vec2End);
	wall->SetOnCollisionCallBack(std::bind(&Wall::ResolvePenetration, this, std::placeholders::_1));
	wall->SetBeginCollisionCallBack(std::bind(&Wall::ResolvePenetration, this, std::placeholders::_1));
}

void Wall::Update()
{
}

void Wall::ResolvePenetration(Collider* _other)
{
	if (_other->GetType() != COLLIDER_TYPE::CIRCLE)
		return;
	else
		ResolveCircle(_other);
	
}

//void Wall::ResolveRectangle(Collider* _other)
//{
//	RectCollider* rectCollider = static_cast<RectCollider*>(_other);
//	Vector2 rectPos = rectCollider->GetPosition();
//	Vector2 rectSize = rectCollider->GetSize();
//	float halfW = rectSize.m_fx / 2.0f;
//	float halfH = rectSize.m_fy / 2.0f;
//
//	Vector2 corners[4] = {
//		{ rectPos.m_fx - halfW, rectPos.m_fy - halfH }, // LeftTop
//		{ rectPos.m_fx + halfW, rectPos.m_fy - halfH }, // RightTop
//		{ rectPos.m_fx + halfW, rectPos.m_fy + halfH }, // RightBottom
//		{ rectPos.m_fx - halfW, rectPos.m_fy + halfH }  // LeftBottom
//	};
//
//	float maxPenetration = 0.0f;
//
//	Vector2 toRect1 = rectPos - m_vec2Start;
//	Vector2 toRect2 = rectPos - m_vec2End;
//	if (Vector2::Dot(toRect1, m_vec2Normal) * Vector2::Dot(toRect2, m_vec2Normal) > 0.0f)
//		return;
//
//	for (int i = 0; i < 4; ++i)
//	{
//		Vector2 toCorner = corners[i] - m_vec2Start;
//		float distToWall = Vector2::Dot(toCorner, m_vec2WallNormal);
//		maxPenetration = (std::min)(maxPenetration, distToWall);
//	}
//
//	if (maxPenetration < 0.0f)
//	{
//		Vector2 pushVec = m_vec2WallNormal * fabsf(maxPenetration);
//
//		Vector2 NewPos = _other->GetTarget()->GetPosition() + pushVec;
//		_other->GetTarget()->SetPosition(NewPos);
//	}
//}

void Wall::ResolveCircle(Collider* _other)
{
	CircleCollider* circleCollider = static_cast<CircleCollider*>(_other);

	Vector2 colliderPos = circleCollider->GetPosition();
	float radius = circleCollider->GetSize();
	
	Vector2 MoveVec = _other->GetTarget()->GetMoveDirection();

	// 직선의 거리 계산
	float A = m_vec2End.m_fy - m_vec2Start.m_fy;
	float B = m_vec2Start.m_fx - m_vec2End.m_fx;
	float C = m_vec2End.m_fx * m_vec2Start.m_fy - m_vec2Start.m_fx * m_vec2End.m_fy;

	float dist = fabsf(A * colliderPos.m_fx + B * colliderPos.m_fy + C) / sqrtf(A * A + B * B);

	Vector2 toStart = colliderPos - m_vec2Start;
	Vector2 toEnd = colliderPos - m_vec2End;
	float dot1 = Vector2::Dot(toStart, m_vec2Normal);
	float dot2 = Vector2::Dot(toEnd, m_vec2Normal);

	if (dist < radius && dot1 * dot2 <= 0.0f)
	{
		// 캐릭터 중심에서 벽의 시작점을 잇는 벡터
		Vector2 centerToLineStart = colliderPos - m_vec2Start;

		// 캐릭터가 벽의 '안쪽'에 있는지 확인 (내적 사용)
		// 만약 wallNormal이 벽의 '바깥쪽'을 가리키지 않는다면 뒤집어 줍니다.
		// wallNormal과 centerToLineStart의 내적이 음수면, 
		// wallNormal이 캐릭터 중심을 향하고 있다는 뜻 (캐릭터가 벽의 안쪽에 있다는 가정)
		float dotProductWithNormal = Vector2::Dot(centerToLineStart, m_vec2WallNormal);

		// 만약 법선이 플레이어 중심 방향을 향하고 있다면 (벽의 바깥쪽을 향하지 않는다면), 뒤집는다.
		// 이렇게 해야 wallNormal이 항상 "플레이어를 벽 밖으로 밀어낼 방향"을 가리킵니다.
		if (dotProductWithNormal < 0.0f)
		{
			m_vec2WallNormal = m_vec2WallNormal * -1.0f;
		}

		// 벽과 수직인 방향으로 튕겨나가는 양(침투 거리)
		float penetration = radius - dist;

		// 플레이어를 법선 방향으로 밀어냄 (이제 wallNormal은 항상 벽의 바깥쪽을 가리킵니다)
		Vector2 NewActorPos = _other->GetTarget()->GetPosition() + (m_vec2WallNormal * penetration);

		// 이동 방향을 슬라이딩 벡터로 보정
		float Dot = Vector2::Dot(MoveVec, m_vec2WallNormal);
		Vector2 slideVec = MoveVec - m_vec2WallNormal * Dot;

		// 새 위치 적용
		_other->GetTarget()->SetPosition(NewActorPos + slideVec * 0.3f);
	}
	
}

