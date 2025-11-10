#pragma once
class RectWall : public Wall
{
public:
	RectWall();
	~RectWall();

	void Update();
	void Render(HDC _memDC) override;
	void Init(Vector2 _)

};

