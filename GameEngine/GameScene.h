#pragma once
#include "Scene.h"
#include "ResourceManager.h"

class UI;
class Player;
class GameMode;
class GameScene : public Scene
{
	enum class UI_TYPE
	{
		START,
		HUD = START,
		MAP,
		TASK_NUMBER_SEQUNECE,
		TASK_DATA_UPLOAD,
		END
	};

private:
	GameMode*				m_GameMode;
	
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

	void OpenUI(int _flagIndex) override;
	void OpenTask(int _flagIndex);

};

