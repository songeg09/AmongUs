#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Init()
{
	for (int i = 0; i != static_cast<int>(COLLISION_TAG::END); ++i)
	{
		m_CollisionGroupList[i] = std::vector<bool>(i + 1, false);
	}
}

void CollisionManager::Update()
{
	for (int i = 0; i != static_cast<int>(COLLISION_TAG::END); ++i)
	{
		for (int j = 0; j < m_CollisionGroupList[i].size(); j++)
		{
			if (m_CollisionGroupList[i][j] == true)
				CollisionCheckGroup(static_cast<COLLISION_TAG>(i), static_cast<COLLISION_TAG>(j));
		}
	}
}

void CollisionManager::RegistCollisionGroup(COLLISION_TAG _eFirst, COLLISION_TAG _eSecond)
{
	if (_eFirst < _eSecond)
	{
		COLLISION_TAG tmp = _eFirst;
		_eFirst = _eSecond;
		_eSecond = tmp;
	}
	m_CollisionGroupList[static_cast<int>(_eFirst)][static_cast<int>(_eSecond)] = true;
}

bool CollisionManager::IsCollision(Collider* _pFirst, Collider* _pSecond)
{
	if (_pFirst->GetType() == _pSecond->GetType())
	{
		if (_pFirst->GetType() == COLLIDER_TYPE::RECTANGLE)
			return IsCollision(static_cast<RectCollider*>(_pFirst), static_cast<RectCollider*>(_pSecond));
		else if (_pFirst->GetType() == COLLIDER_TYPE::CIRCLE)
			return IsCollision(static_cast<CircleCollider*>(_pFirst), static_cast<CircleCollider*>(_pSecond));
		else
			return IsCollision(static_cast<LineCollider*>(_pFirst), static_cast<LineCollider*>(_pSecond));
	}
	else
	{
		if (_pFirst->GetType() == COLLIDER_TYPE::RECTANGLE)
		{
			if (_pSecond->GetType() == COLLIDER_TYPE::CIRCLE)
				return IsCollision(static_cast<RectCollider*>(_pFirst), static_cast<CircleCollider*>(_pSecond));
			else
				return IsCollision(static_cast<RectCollider*>(_pFirst), static_cast<LineCollider*>(_pSecond));
		}
		else if (_pFirst->GetType() == COLLIDER_TYPE::CIRCLE)
		{
			if (_pSecond->GetType() == COLLIDER_TYPE::RECTANGLE)
				return IsCollision(static_cast<CircleCollider*>(_pFirst), static_cast<RectCollider*>(_pSecond));
			else
				return IsCollision(static_cast<CircleCollider*>(_pFirst), static_cast<LineCollider*>(_pSecond));
		}
		else
		{
			if (_pSecond->GetType() == COLLIDER_TYPE::RECTANGLE)
				return IsCollision(static_cast<LineCollider*>(_pFirst), static_cast<RectCollider*>(_pSecond));
			else
				return IsCollision(static_cast<LineCollider*>(_pFirst), static_cast<CircleCollider*>(_pSecond));
		}
	}
}

bool CollisionManager::IsCollision(RectCollider* _pFirst, RectCollider* _pSecond)
{
	if (_pFirst->isEnable() == false || _pSecond->isEnable() == false)
		return false;
	Vector2 FirstPosition = _pFirst->GetPosition();
	Vector2 FirstSize = _pFirst->GetSize();
	Vector2 SecondPosition = _pSecond->GetPosition();
	Vector2 SecondSize = _pSecond->GetSize();

	Vector2 CollisionPosition = FirstPosition - SecondPosition;

	if (abs(CollisionPosition.m_fx) < (FirstSize.m_fx + SecondSize.m_fx) / 2.0f &&
		abs(CollisionPosition.m_fy) < (FirstSize.m_fy + SecondSize.m_fy) / 2.0f)
	{
		return true;
	}
	return false;
}

bool CollisionManager::IsCollision(CircleCollider* _pFirst, CircleCollider* _pSecond)
{
	if (_pFirst->isEnable() == false || _pSecond->isEnable() == false)
		return false;
	Vector2 FirstPosition = _pFirst->GetPosition();
	Vector2 SecondPosition = _pSecond->GetPosition();
	float CircleLength = (FirstPosition - SecondPosition).Length();
	float SumRadius = _pFirst->GetSize() + _pSecond->GetSize();
	if (CircleLength <= SumRadius)
		return true;
	else
		return false;
}

bool CollisionManager::IsCollision(RectCollider* _pRect, CircleCollider* _pCircle)
{
	if (_pRect->isEnable() == false || _pCircle->isEnable() == false)
		return false;

	Vector2 vecCirclePosition = _pCircle->GetPosition();
	float fRadius = _pCircle->GetSize();

	Rect Rect = _pRect->GetRect();

	if (vecCirclePosition.m_fx >= Rect.left && vecCirclePosition.m_fx <= Rect.right ||
		vecCirclePosition.m_fy >= Rect.top && vecCirclePosition.m_fy <= Rect.bottom)
	{
		Rect = { Rect.left - fRadius,
				   Rect.top - fRadius,
				   Rect.right + fRadius,
				   Rect.bottom + fRadius, };
		if (vecCirclePosition.m_fx >= Rect.left && vecCirclePosition.m_fx <= Rect.right &&
			vecCirclePosition.m_fy >= Rect.top && vecCirclePosition.m_fy <= Rect.bottom)
			return true;
	}
	else
	{
		Vector2 vecLeftTop = { Rect.left,Rect.top };
		Vector2 vecRightTop = { Rect.right,Rect.top };
		Vector2 vecLeftBottom = { Rect.left,Rect.bottom };
		Vector2 vecRightBottom = { Rect.right,Rect.bottom };

		if ((vecCirclePosition - vecLeftTop).Length() <= _pCircle->GetSize())
			return true;
		else if ((vecCirclePosition - vecRightTop).Length() <= _pCircle->GetSize())
			return true;
		else if ((vecCirclePosition - vecLeftBottom).Length() <= _pCircle->GetSize())
			return true;
		else if ((vecCirclePosition - vecRightBottom).Length() <= _pCircle->GetSize())
			return true;
	}
	return false;
}

bool CollisionManager::IsCollision(LineCollider* _pFirst, LineCollider* _pSecond)
{
	return Vector2::IsLineIntersect(
		_pFirst->GetStart(), _pFirst->GetEnd(),
		_pSecond->GetStart(), _pSecond->GetEnd()
	);
}

bool CollisionManager::IsCollision(LineCollider* _pLine, CircleCollider* _pCircle)
{
	Vector2 lineVec = _pLine->GetEnd() - _pLine->GetStart();
	Vector2 toCircle = _pCircle->GetPosition() - _pLine->GetStart();

	float lineVecLength = lineVec.Length();

	// 엣지 케이스 라인의 길이가 0인 경우
	if (lineVecLength == 0.0f)
		return toCircle.Length() <= _pCircle->GetSize();

	float t = Vector2::Dot(toCircle, lineVec) / (lineVecLength * lineVecLength);
	t = std::clamp(t, 0.0f, 1.0f);

	Vector2 closestPoint = _pLine->GetStart() + (lineVec * t);
	Vector2 distVec = _pCircle->GetPosition() - closestPoint;

	return distVec.Length() <= _pCircle->GetSize();
}

bool CollisionManager::IsCollision(LineCollider* _pLine, RectCollider* _pRect)
{
	Vector2 RectPos = _pRect->GetPosition();
	float halfW = _pRect->GetSize().m_fx / 2.0f;
	float halfH = _pRect->GetSize().m_fy / 2.0f;

	float left = RectPos.m_fx - halfW;
	float top = RectPos.m_fy - halfH;
	float right = RectPos.m_fx + halfW;
	float bottom = RectPos.m_fy + halfH;
	
	Vector2 LineStart = _pLine->GetStart();
	Vector2 LineEnd = _pLine->GetEnd();
	Vector2 LeftTop(left, top);
	Vector2 LeftBottom(left, bottom);
	Vector2 RightTop(right, top);
	Vector2 RigthBottom(right, bottom);

	if (Vector2::IsLineIntersect(LeftTop, LeftBottom, LineStart, LineEnd) ||
		Vector2::IsLineIntersect(LeftTop, RightTop, LineStart, LineEnd) ||
		Vector2::IsLineIntersect(LeftBottom, RigthBottom, LineStart, LineEnd) ||
		Vector2::IsLineIntersect(RightTop, RigthBottom, LineStart, LineEnd))
		return true;

	return false;
}

void CollisionManager::ReleaseCollisionGroup()
{
	for (int i = 0; i != static_cast<int>(COLLISION_TAG::END); ++i)
	{
		for (int j = 0; j < m_CollisionGroupList[i].size(); ++j)
			m_CollisionGroupList[i][j] = false;
	}
}

void CollisionManager::CollisionCheckGroup(COLLISION_TAG _eFirst, COLLISION_TAG _eSecond)
{
	Scene* CurScene = SceneManager::GetInstance()->GetCurScene();
	const std::vector<Collider*>& FirstGroup = CurScene->GetCollisionTagGroup(_eFirst);
	const std::vector<Collider*>& SecondGroup = CurScene->GetCollisionTagGroup(_eSecond);

	for (int i = 0; i < FirstGroup.size(); ++i)
	{
		for (int j = 0; j < SecondGroup.size(); ++j)
		{
			if (FirstGroup[i] == SecondGroup[j])
				continue;

			CollisionCheck(FirstGroup, SecondGroup);
		}
	}
}

void CollisionManager::CollisionCheck(const std::vector<Collider*>& _pFirst, const std::vector<Collider*>& _pSecond)
{
	for (Collider* first : _pFirst)
	{
		for (Collider* second : _pSecond)
		{
			Collider_ID ID;
			ID.iFirst_ID = first->GetID();
			ID.iSecond_ID = second->GetID();

			std::map<unsigned long long, bool>::iterator iter = m_PrevCollision.find(ID.ID);

			if (iter == m_PrevCollision.end())
			{
				m_PrevCollision.insert(std::make_pair(ID.ID, false));
				iter = m_PrevCollision.find(ID.ID);
			}

			if (IsCollision(first, second) == true)
			{
				if (iter->second == true)
				{
					first->OnCollision(second);
					second->OnCollision(first);
				}
				else
				{
					first->BeginCollision(second);
					second->BeginCollision(first);
					iter->second = true;
				}
			}
			else
			{
				if (iter->second == true)
				{
					first->EndCollision(second);
					second->EndCollision(first);
					iter->second = false;
				}
			}
		}
	}
}