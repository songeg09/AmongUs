#pragma once
#include "Scene.h"
#include "ResourceManager.h"

class UI;
class Character;
class GameScene : public Scene
{
	enum UI_MODE
	{
		HUD,
		MAP,
		END
	};


private:
	Texture* m_pBackGround;
	Vector2 m_vec2BackGroundPosition;	
	Character* m_Player;

	UI* m_arrUIs[UI_MODE::END];
	UI_MODE				m_eCurUI;

public:
	GameScene(std::wstring _strName);
	~GameScene();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	
	Vector2 GetViewPortTopLeftInScene() override;
	Vector2 GetBackBufferTopLeftInScene() override;
};

