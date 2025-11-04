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
	std::map<unsigned long long, bool> m_PrevCollision;
	std::vector<bool> m_CollisionGroupList[static_cast<int>(OBJECT_GROUP::END)];
public:
	void Init();
	void Update();
	void RegistCollisionGroup(OBJECT_GROUP _eFirst, OBJECT_GROUP _eSecond);
	bool IsCollision(Collider* _pFirst, Collider* _pSecond);
	bool IsCollision(RectCollider* _pFirst, RectCollider* _pSecond);
	bool IsCollision(CircleCollider* _pFirst, CircleCollider* _pSecond);
	bool IsCollision(RectCollider* _pRect, CircleCollider* _pCircle);
	void ReleaseCollisionGroup();
	void CollisionCheckGroup(OBJECT_GROUP _eFirst, OBJECT_GROUP _eSecond);
	void CollisionCheck(const std::list<Collider*>& _pFirst, const std::list<Collider*>& _pSecond);
};

