#pragma once

class Collider;
class Wall : public Object
{
private:
	Collider* m_pWallCollider;

public:
	Wall();
	virtual ~Wall();

	void Update() override;
	void Render(HDC _memDC) override;
	void Init(Vector2 _vec2Position);
	void ResolvePenetration(Collider* _pOther) = 0;

};

