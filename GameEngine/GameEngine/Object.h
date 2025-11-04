#pragma once
#include"ResourceManager.h"

class Collider;
class Object
{
private:
	Vector2					m_vec2Position;
	Vector2					m_vec2Scale;
	std::list<Collider*>	m_pColliderList;

public:
	Object();
	virtual ~Object();

	virtual void Update() = 0;
	virtual void LateUpdate() final; // 자식 Class에서 Override하지 못하게 막는 용도
	virtual void Render(HDC _memDC);
	virtual void Init(Vector2 _vec2Position);

	Collider* CreateRectCollider(bool _eEnabled, Vector2 _vecSize, Vector2 _vecOffset = Vector2{ 0.0f,0.0f });
	Collider* CreateCircleCollider(bool _eEnabled, float _fRadius, Vector2 _vecOffset = Vector2{ 0.0f,0.0f });
	void ColliderRender(HDC _memDC);
	inline bool UseCollider() { return m_pColliderList.size() != 0; }

	inline const std::list<Collider*>& GetColliderList() { return m_pColliderList; }
	inline void AddPosition(Vector2 _vec2Add) { m_vec2Position += _vec2Add; }
	inline void SetPosition(Vector2 _vec2Position) { m_vec2Position = _vec2Position; }
	inline void SetScale(Vector2 _vec2Scale) { m_vec2Scale = _vec2Scale; }
	inline Vector2 GetPosition() { return m_vec2Position; }
	inline Vector2 GetScale() { return m_vec2Scale; }
};

