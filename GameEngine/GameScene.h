#pragma once
#include "Scene.h"
#include "MinimapProvider.h"
#include "ResourceManager.h"

class Player;
class GameMode;
class GameObject;
class Interactable;
class GameScene : public Scene, public MinimapProvider
{
	enum class UI_TYPE
	{
		START,
		HUD = START,
		MAP,
		TASK_NUMBER_SEQUNECE,
		TASK_DATA_UPLOAD,
		TASK_TIMED_BUTTONS,
		END
	};

private:
	GameMode*				m_GameMode;

	Texture*				m_pBackGround;
	Vector2					m_vec2BackGroundPosition;	
	Player*					m_Player;

	std::set<Interactable*>	m_setTasksLeft;

	float					m_fTotalTaskProgress;

public:
	GameScene(std::wstring _strName);
	~GameScene();
	
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	
	void InitUI();


	Vector2 GetViewPortTopLeftInScene() override;
	Vector2 GetBackBufferTopLeftInScene() override;

	void OpenUI(int _flagIndex) override;
	void OpenTask(int _flagIndex);

	Vector2 GetPlayerPos() const override;
	const std::set<Interactable*>& GetGameObjects() const override { return m_setTasksLeft; }

	void OnTaskSuccess();

};

