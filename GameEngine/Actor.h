#pragma once
#include "Object.h"
#include "Animation.h"
enum class ACTOR_TYPE
{
	PLAYER,
	MONSTER
};

class Actor : public Object
{
private:
	std::vector<Animation>	m_AnimationList[DIRECTION::END];
	int						m_iCurAnimation;
	DIRECTION				m_eDirection;
	bool					m_bMovable;
	float					m_fMoveSpeed;
	Vector2					m_vec2Force;
	ACTOR_TYPE m_eActorType;

public:
	Actor();
	virtual ~Actor();
	virtual void Attack(Collider* _pOther) = 0;
	inline void SetMovable(bool _bMovable) { m_bMovable = _bMovable; }
	inline bool IsMovable() { return m_bMovable == true; }
	inline void AddForce(Vector2 _vec2Force) { m_vec2Force += _vec2Force; }
	inline void SetForce(Vector2 _vec2Force) { m_vec2Force = _vec2Force; }
	inline void SetVelocity(Vector2 _vec2Force) { m_vec2Force = _vec2Force; }
	inline void ResetForce() { m_vec2Force = {}; }
	inline void SetActorType(ACTOR_TYPE _eActorType) { m_eActorType = _eActorType; }
	inline ACTOR_TYPE GetActorType() { return m_eActorType; }

	void Update() override;
	void Render(HDC _memDC) override;
	void Init(Vector2 _vec2Position) override;
	inline DIRECTION GetDirection() { return m_eDirection; }

	void SetAnimation(int _iIndex);
	inline int GetCurAnimation() { return m_iCurAnimation; }

protected:
	
	void SetAnimationEvent(int _iIndex, int _iTextureIndex, std::function<void()> _pCallBack);
	void InitAnimation(int _iIndex, int _iStartTextureIndex, int _iEndTextureIndex,
		float _fPlaySpeed = 1.0f, ANIMATION_TYPE _eAnimationType = ANIMATION_TYPE::LOOP, ANCHOR _eAnchor = ANCHOR::CENTER);

	inline void SetDirection(DIRECTION _eDirection) { m_eDirection = _eDirection; }
	inline void SetMoveSpeed(float _fMoveSpeed) { m_fMoveSpeed = _fMoveSpeed; }

	

	void Move(Vector2 _vec2Force);
	void ResizeAnimation(int _iSize);
};

