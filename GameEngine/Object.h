#pragma once
#include"ResourceManager.h"

class Collider;
class WallDetector;
class Object : public std::enable_shared_from_this<Object>
{
private:
	Vector2								m_vec2Position;
	Vector2								m_vec2MoveVec;
	Vector2								m_vec2Scale;
	std::list<std::weak_ptr<Collider>>	m_pColliderList;

public:
	Object();
	virtual ~Object();

	virtual void Update() = 0;
	virtual void LateUpdate() final; // 자식 Class에서 Override하지 못하게 막는 용도
	virtual void Render(HDC _memDC);
	virtual void Init(Vector2 _vec2Position);

	std::shared_ptr<Collider> CreateRectCollider(COLLISION_TAG _eTag, bool _eEnabled, Vector2 _vecSize, Vector2 _vecOffset = Vector2{ 0.0f,0.0f });
	std::shared_ptr<Collider> CreateCircleCollider(COLLISION_TAG _eTag, bool _eEnabled, float _fRadius, Vector2 _vecOffset = Vector2{ 0.0f,0.0f });
	std::shared_ptr<WallDetector> CreateWallDetector(Vector2 _vec2Offset, float _fRadius);

	void ColliderRender(HDC _memDC);
	bool UseCollider() { return m_pColliderList.size() != 0; }

	void AddPosition(Vector2 _vec2Add) { 
		m_vec2MoveVec = _vec2Add;
		m_vec2MoveVec.Normalize();
		m_vec2Position += _vec2Add; 
	}
	Vector2 GetMoveDirection() {return m_vec2MoveVec;}
	void SetPosition(Vector2 _vec2Position) { m_vec2Position = _vec2Position; }
	void SetScale(Vector2 _vec2Scale) { m_vec2Scale = _vec2Scale; }
	Vector2 GetPosition() const { return m_vec2Position; }
	Vector2 GetScale() { return m_vec2Scale; }
};

