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

void CollisionManager::AddCollider(COLLISION_TAG _tag, std::shared_ptr<Collider> _collider)
{
	m_arrColliders[static_cast<int>(_tag)].push_back(_collider);
}

void CollisionManager::ClearColliders()
{
	for (int i = 0; i < static_cast<int>(COLLISION_TAG::END); ++i)
		m_arrColliders[i].clear();
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
			return IsCollision(static_cast<CircleCollider*>(_pFirst), static_cast<RectCollider*>(_pSecond));
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
	for (int i = 0; i != static_cast<int>(COLLISION_TAG::END); ++i)
	{
		for (int j = 0; j < m_CollisionGroupList[i].size(); ++j)
			m_CollisionGroupList[i][j] = false;
	}
}

void CollisionManager::CollisionCheckGroup(COLLISION_TAG _eFirst, COLLISION_TAG _eSecond)
{
	const std::vector<std::weak_ptr<Collider>>& FirstGroup = m_arrColliders[static_cast<int>(_eFirst)];
	const std::vector<std::weak_ptr<Collider>>& SecondGroup = m_arrColliders[static_cast<int>(_eSecond)];

	for (std::weak_ptr<Collider> first: FirstGroup)
	{
		for (std::weak_ptr<Collider> second : SecondGroup)
		{
			if (first.lock().get() == second.lock().get())
				continue;

			CollisionCheck(first.lock().get(), second.lock().get());
		}
	}
}

void CollisionManager::CollisionCheck(Collider* _pFirst, Collider* _pSecond)
{
	Collider_ID ID;
	ID.iFirst_ID = _pFirst->GetID();
	ID.iSecond_ID = _pSecond->GetID();

	std::map<unsigned long long, bool>::iterator iter = m_PrevCollision.find(ID.ID);

	if (iter == m_PrevCollision.end())
	{
		m_PrevCollision.insert(std::make_pair(ID.ID, false));
		iter = m_PrevCollision.find(ID.ID);
	}

	if (IsCollision(_pFirst, _pSecond) == true)
	{
		if (iter->second == true)
		{
			_pFirst->OnCollision(_pSecond);
			_pSecond->OnCollision(_pFirst);
		}
		else
		{
			_pFirst->BeginCollision(_pSecond);
			_pSecond->BeginCollision(_pFirst);
			iter->second = true;
		}
	}
	else
	{
		if (iter->second == true)
		{
			_pFirst->EndCollision(_pSecond);
			_pSecond->EndCollision(_pFirst);
			iter->second = false;
		}
	}
}