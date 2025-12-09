#pragma once
enum class COLLIDER_TYPE
{
	RECTANGLE,
	CIRCLE,
};

class Object;
class Collider abstract : public std::enable_shared_from_this<Collider>
{
private:
	static unsigned int						s_uID;
	std::weak_ptr<Object>					m_pTarget;
	Vector2									m_vecOffset;
	Vector2									m_vecPosition;
	const unsigned int						m_uID;
	int										m_iCollisionCount;
	bool									m_bEnabled;
	COLLIDER_TYPE							m_eColliderType;
	COLLISION_TAG							m_eTag;
	std::function<void(Collider* _pOther)>	m_OnCollisioncallBack;
	std::function<void(Collider* _pOther)>	m_BeginCollisioncallBack;
	std::function<void(Collider* _pOther)>	m_EndCollisioncallBack;
public:
	void Init(COLLISION_TAG _eTag, bool _bEnabled, Vector2 _vecOffset);
	void Regist();
	inline void SetOnCollisionCallBack(std::function<void(Collider* _pOther)> _pCallBack) { m_OnCollisioncallBack = _pCallBack; }
	inline void SetBeginCollisionCallBack(std::function<void(Collider* _pOther)> _pCallBack) { m_BeginCollisioncallBack = _pCallBack; }
	inline void SetEndCollisionCallBack(std::function<void(Collider* _pOther)> _pCallBack) { m_EndCollisioncallBack = _pCallBack; }
	inline void SetOffsetPosition(Vector2 _vecPosition) { m_vecOffset = _vecPosition; }
	inline void SetTarget(std::shared_ptr<Object> _pTarget) { m_pTarget = _pTarget; }
	inline void SetType(COLLIDER_TYPE _eColliderType) { m_eColliderType = _eColliderType; }

	void OnCollision(Collider* _pOther);
	void BeginCollision(Collider* _pOther);
	void EndCollision(Collider* _pOther);

	inline unsigned int GetID() { return m_uID; }
	inline Vector2 GetOffsetPosition() { return m_vecOffset; }
	inline Vector2 GetPosition() { return m_vecPosition; }
	inline Object* GetTarget() { return m_pTarget.lock().get(); }
	inline bool isEnable() { return m_bEnabled; }
	inline void SetEnable(bool _bEnabled) { m_bEnabled = _bEnabled; }
	int GetCollisionCount() { return m_iCollisionCount; }
	COLLIDER_TYPE GetType() { return m_eColliderType; }
	COLLISION_TAG GetTag() { return m_eTag; }

	void FinalUpdate();
	virtual void Render(HDC _memDC) = 0;

	Collider();
	virtual ~Collider();
};

class RectCollider : public Collider
{
private:
	Vector2 m_vecSize;

public:
	RectCollider();
	~RectCollider();

	void Init(COLLISION_TAG _eTag, bool _bEnabled, Vector2 _vecSize, Vector2 _vecOffset = Vector2{ 0.0f,0.0f });
	void Render(HDC _memDC) override;
	Rect GetRect();
	void SetSize(Vector2 _vecSize) { m_vecSize = _vecSize; }
	Vector2 GetSize() { return m_vecSize; }
};

class CircleCollider : public Collider
{
private:
	float m_fRadius;
public:
	CircleCollider();
	~CircleCollider();

	void Init(COLLISION_TAG _eTag, bool _bEnabled, float _fRadius, Vector2 _vecOffset = Vector2{ 0.0f,0.0f });
	void Render(HDC _memDC) override;
	void SetSize(float _fRadius) { m_fRadius = _fRadius; }
	float GetSize() { return m_fRadius; }
};
