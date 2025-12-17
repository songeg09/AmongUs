#pragma once
#include "Scene.h"
#include "IMinimapProvider.h"
#include "ResourceManager.h"

class Player;
class Ghost;
class GameMode;
class GameObject;
class Interactable;
class IAttemptable;
class Vent;
class GameScene : public Scene, public IMinimapProvider, public std::enable_shared_from_this<GameScene>
{
	enum class UI_TYPE
	{
		START,
		HUD = START,
		MAP,
		MENU,
		RESULT,
		TASK_NUMBER_SEQUNECE,
		TASK_DATA_UPLOAD,
		TASK_TIMED_BUTTONS,
		END
	};

private:
	std::shared_ptr<GameMode>					m_GameMode;
	std::weak_ptr<Texture>						m_pBackGround;
	std::weak_ptr<Player>						m_Player;

	std::set<IAttemptable*>						m_setTasksLeft;

public:
	GameScene(std::wstring _strName);
	~GameScene();
	
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC _memDC) override;
	
	void InitUI();
	void InstantiateObjects();

	Vector2 GetViewPortTopLeftInScene() override;
	Vector2 GetBackBufferTopLeftInScene() override;

	void OpenUI(int _flagIndex) override;
	void OpenTask(int _flagIndex);

	Vector2 GetPlayerPos() const override;
	const std::set<IAttemptable*>& GetGameObjects() const override { return m_setTasksLeft; }

	void OnTaskSuccess();
	void OnTaskFail();

};