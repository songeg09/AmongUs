#pragma once

union Collider_ID
{
	struct
	{
		unsigned int iFirst_ID;
		unsigned int iSecond_ID;
	};
	unsigned long long ID;
};

class RectCollider;
class CircleCollider;
class Collider;
class CollisionManager
{
	SINGLETON(CollisionManager)
private:
	std::map<unsigned long long, bool>				m_PrevCollision;
	std::vector<bool>								m_CollisionGroupList[static_cast<int>(COLLISION_TAG::END)];
	std::vector<std::weak_ptr<Collider>>			m_arrColliders[static_cast<int>(COLLISION_TAG::END)];

public:
	void Init();
	void Update();
	void RegistCollisionGroup(COLLISION_TAG _eFirst, COLLISION_TAG _eSecond);

	void RegistCollider(std::shared_ptr<Collider> _collider);
	void UnregistCollider(std::shared_ptr<Collider> _collider);

	bool IsCollision(Collider* _pFirst, Collider* _pSecond);
	bool IsCollision(RectCollider* _pFirst, RectCollider* _pSecond);
	bool IsCollision(RectCollider* _pRect, CircleCollider* _pCircle);
	bool IsCollision(CircleCollider* _pFirst, CircleCollider* _pSecond);
	bool IsCollision(CircleCollider* _pCircle, RectCollider* _pRect) { return IsCollision(_pRect, _pCircle); }

	void ReleaseCollisionGroup();
	void CollisionCheckGroup(COLLISION_TAG _eFirst, COLLISION_TAG _eSecond);
	void CollisionCheck(Collider* _pFirst, Collider* _pSecond);
};

