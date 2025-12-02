#pragma once
#include "Object.h"

class Collider;
class Wall : public Object
{
private:
	Vector2 m_vec2Start;
	Vector2 m_vec2End;
	Vector2 m_vec2Normal;
	Vector2 m_vec2WallNormal;
	float	m_fLineLen;

public:
	Wall();
	virtual ~Wall();

	void Init(Vector2 _vec2Start, Vector2 _vec2End);
	void Update() override;
	void ResolvePenetration(Collider* _other);
	//void ResolveRectangle(Collider* _other);
	void ResolveCircle(Collider* _other);
};

