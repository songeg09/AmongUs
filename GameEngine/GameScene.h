#pragma once
#include "Scene.h"
#include "ResourceManager.h"

class UI;
class Player;
class GameMode;
class GameScene : public Scene
{

private:
	GameMode*				m_GameMode;
	Flags					m_UIFlags;
	Texture*				m_pBackGround;
	Vector2					m_vec2BackGroundPosition;	
	Player*					m_Player;



public:
	GameScene(std::wstring _strName);
	~GameScene();
	
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	
	Vector2 GetViewPortTopLeftInScene() override;
	Vector2 GetBackBufferTopLeftInScene() override;

	void UpdateUIVisibility();
};

