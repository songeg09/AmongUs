#pragma once
#include "Scene.h"
#include "ResourceManager.h"

class GameScene : public Scene
{
private:
	Texture* m_pBackGround;
	Vector2 m_vec2BackGroundPosition;
public:
	GameScene(std::wstring _strName);
	~GameScene();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
};

