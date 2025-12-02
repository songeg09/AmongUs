#pragma once

class WallDetector;
class Wall
{
private:
	Vector2 m_vec2Start;
	Vector2 m_vec2End;
	Vector2 m_vec2LineDir;
	Vector2 m_vec2WallNormal;
	float	m_fLineLen;

public:
	Wall();
	virtual ~Wall();

	void Init(Vector2 _vec2Start, Vector2 _vec2End);
	void Render(HDC _memDC);

	void ResolvePenetration(WallDetector* _other);
};

