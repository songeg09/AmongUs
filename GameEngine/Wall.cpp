#include "pch.h"
#include "Object.h"
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
	if (_other->GetType() == COLLIDER_TYPE::LINE)
		return;
	else if (_other->GetType() == COLLIDER_TYPE::CIRCLE)
		ResolveCircle(_other);
	else
		ResolveRectangle(_other);
	
}

void Wall::ResolveRectangle(Collider* _other)
{
	RectCollider* rectCollider = static_cast<RectCollider*>(_other);
	Vector2 rectPos = rectCollider->GetPosition();
	Vector2 rectSize = rectCollider->GetSize();
	float halfW = rectSize.m_fx / 2.0f;
	float halfH = rectSize.m_fy / 2.0f;

	Vector2 corners[4] = {
		{ rectPos.m_fx - halfW, rectPos.m_fy - halfH }, // LeftTop
		{ rectPos.m_fx + halfW, rectPos.m_fy - halfH }, // RightTop
		{ rectPos.m_fx + halfW, rectPos.m_fy + halfH }, // RightBottom
		{ rectPos.m_fx - halfW, rectPos.m_fy + halfH }  // LeftBottom
	};

	float maxPenetration = 0.0f;

	Vector2 toPlayer = rectPos - m_vec2Start;
	if (Vector2::Dot(toPlayer, m_vec2WallNormal) < 0.0f)
	{
		m_vec2WallNormal = m_vec2WallNormal * -1.0f;
	}

	for (int i = 0; i < 4; ++i)
	{
		Vector2 toCorner = corners[i] - m_vec2Start;
		float distToWall = Vector2::Dot(toCorner, m_vec2WallNormal);
		maxPenetration = (std::min)(maxPenetration, distToWall);
	}

	if (maxPenetration < 0.0f)
	{
		Vector2 pushVec = m_vec2WallNormal * (fabsf(maxPenetration) + 1.0f);

		Vector2 NewPos = _other->GetTarget()->GetPosition() + pushVec;
		_other->GetTarget()->SetPosition(NewPos);
	}
}

void Wall::ResolveCircle(Collider* _other)
{
	//Vector2 centerToLineStart = _other->GetTarget()->GetPosition() - m_vec2Start;

	//float dotProductWithNormal = Vector2::Dot(centerToLineStart, m_vec2WallNormal);

	//if (dotProductWithNormal < 0.0f)
	//{
	//	m_vec2WallNormal = m_vec2WallNormal * -1.0f;
	//}

	//float penetration = _other->GetSize() - dist;

	//Vector2 AdjustedPos = _other->GetTarget()->GetPosition() + (m_vec2WallNormal * penetration);

	//float Dot = MoveVec.Dot(line.wallNormal);
	//Vector2 slideVec = MoveVec - line.wallNormal * Dot;

	//// 새 위치 적용
	//SetPosition(playerPos + slideVec * 0.3f);
}


