#pragma once
#include "Object.h"
#include "Animation.h"
#include "AnimationData.h"
enum class ACTOR_TYPE
{
	PLAYER,
	NPC
};

class Actor : public Object
{
private:
	std::vector<Animation>	m_AnimationList[2];
	int						m_iCurAnimation;
	DIRECTION				m_eDirection;
	float					m_fMoveSpeed;
	Vector2					m_vec2Force;

public:
	Actor();
	virtual ~Actor();
	void AddForce(Vector2 _vec2Force) { m_vec2Force += _vec2Force; }
	void SetForce(Vector2 _vec2Force) { m_vec2Force = _vec2Force; }
	Vector2 GetForce() { return m_vec2Force; }
	void SetVelocity(Vector2 _vec2Force) { m_vec2Force = _vec2Force; }
	void ResetForce() { m_vec2Force = {}; }

	void Update() override;
	void Render(HDC _memDC) override;
	void Init(Vector2 _vec2Position) override;
	inline DIRECTION GetDirection() { return m_eDirection; }

	void SetAnimation(int _iIndex);
	inline int GetCurAnimation() { return m_iCurAnimation; }

protected:
	
	void SetAnimationEvent(int _iIndex, int _iTextureIndex, std::function<void()> _pCallBack);
	void InitAnimation(int _iIndex, AnimationData _data);

	inline void SetDirection(DIRECTION _eDirection) { m_eDirection = _eDirection; }
	inline void SetMoveSpeed(float _fMoveSpeed) { m_fMoveSpeed = _fMoveSpeed; }
	
	void Move(Vector2 _vec2Force);
	void ResizeAnimation(int _iSize);

};

