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
	for (int i = 0; i != static_cast<int>(OBJECT_GROUP::END); ++i)
	{
		m_CollisionGroupList[i] = std::vector<bool>(i + 1, false);
	}
}

void CollisionManager::Update()
{
	for (int i = 0; i != static_cast<int>(OBJECT_GROUP::END); ++i)
	{
		for (int j = 0; j < m_CollisionGroupList[i].size(); j++)
		{
			if (m_CollisionGroupList[i][j] == true)
				CollisionCheckGroup(static_cast<OBJECT_GROUP>(i), static_cast<OBJECT_GROUP>(j));
		}
	}
}

void CollisionManager::RegistCollisionGroup(OBJECT_GROUP _eFirst, OBJECT_GROUP _eSecond)
{
	if (_eFirst < _eSecond)
	{
		OBJECT_GROUP tmp = _eFirst;
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
		else
			return IsCollision(static_cast<CircleCollider*>(_pFirst), static_cast<CircleCollider*>(_pSecond));
	}
	else
	{
		if (_pFirst->GetType() == COLLIDER_TYPE::RECTANGLE)
			return IsCollision(static_cast<RectCollider*>(_pFirst), static_cast<CircleCollider*>(_pSecond));
		else
			return IsCollision(static_cast<RectCollider*>(_pSecond), static_cast<CircleCollider*>(_pFirst));
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

void CollisionManager::ReleaseCollisionGroup()
{
	for (int i = 0; i != static_cast<int>(OBJECT_GROUP::END); ++i)
	{
		for (int j = 0; j < m_CollisionGroupList[i].size(); ++j)
			m_CollisionGroupList[i][j] = false;
	}
}

void CollisionManager::CollisionCheckGroup(OBJECT_GROUP _eFirst, OBJECT_GROUP _eSecond)
{
	Scene* CurScene = SceneManager::GetInstance()->GetCurScene();
	const std::vector<Object*>& FirstGroup = CurScene->GetObjectGroup(_eFirst);
	const std::vector<Object*>& SecondGroup = CurScene->GetObjectGroup(_eSecond);

	for (int i = 0; i < FirstGroup.size(); ++i)
	{
		if (FirstGroup[i]->UseCollider() == false)
			continue;
		for (int j = 0; j < SecondGroup.size(); ++j)
		{
			if (FirstGroup[i] == SecondGroup[j])
				continue;
			if (SecondGroup[j]->UseCollider() == false)
				continue;

			CollisionCheck(FirstGroup[i]->GetColliderList(), SecondGroup[j]->GetColliderList());
		}
	}
}

void CollisionManager::CollisionCheck(const std::list<Collider*>& _pFirst, const std::list<Collider*>& _pSecond)
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