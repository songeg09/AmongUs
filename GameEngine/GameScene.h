#pragma once
#include "Scene.h"
#include "ResourceManager.h"

class Character;
class GameScene : public Scene
{
private:
	Texture* m_pBackGround;
	Vector2 m_vec2BackGroundPosition;	
	Character* m_Player;
public:
	GameScene(std::wstring _strName);
	~GameScene();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	
	Vector2 GetViewPortTopLeftInScene() override;
	Vector2 GetBackBufferTopLeftInScene() override;
};

