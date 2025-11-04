#pragma once
#include "RectZone.h"
class SwordBeamObject : public RectZone
{
private:
	DIRECTION m_eDirection;
	Vector2 m_vec2InitialPos;
	Vector2 m_vec2DestPos;
	float m_fRange;
	float m_fSpeed;

public:
	void Init(int _iIndex, DIRECTION m_eDirection, Vector2 _vec2InitialPos, float _fRange, float _fSpeed);
	void Update() override;
	void SetInitialPos(Vector2 _vec2InitialPos) { m_vec2InitialPos = _vec2InitialPos; }
	
	Vector2 GetDirectionVector(DIRECTION _direction);
};

