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
class LineCollider;
class Collider;
class CollisionManager
{
	SINGLETON(CollisionManager)
private:
	std::map<unsigned long long, bool> m_PrevCollision;
	std::vector<bool> m_CollisionGroupList[static_cast<int>(COLLISION_TAG::END)];
public:
	void Init();
	void Update();
	void RegistCollisionGroup(COLLISION_TAG _eFirst, COLLISION_TAG _eSecond);
	bool IsCollision(Collider* _pFirst, Collider* _pSecond);
	
	bool IsCollision(RectCollider* _pFirst, RectCollider* _pSecond);
	bool IsCollision(RectCollider* _pRect, CircleCollider* _pCircle);
	bool IsCollision(RectCollider* _pRect, LineCollider* _pLine) { return IsCollision(_pLine, _pRect); }
	
	bool IsCollision(CircleCollider* _pFirst, CircleCollider* _pSecond);
	bool IsCollision(CircleCollider* _pCircle, RectCollider* _pRect) { return IsCollision(_pRect, _pCircle); }
	bool IsCollision(CircleCollider* _pCircle, LineCollider* _pLine) { return IsCollision(_pLine, _pCircle); }
	
	bool IsCollision(LineCollider* _pFirst, LineCollider* _pSecond);
	bool IsCollision(LineCollider* _pLine, CircleCollider* _pCircle);
	bool IsCollision(LineCollider* _pLine, RectCollider* _pRect);

	void ReleaseCollisionGroup();
	void CollisionCheckGroup(COLLISION_TAG _eFirst, COLLISION_TAG _eSecond);
	void CollisionCheck(const std::vector<Collider*>& _pFirst, const std::vector<Collider*>& _pSecond);
};

