#pragma once
#include "Scene.h"
#include "MinimapProvider.h"
#include "ResourceManager.h"

class Player;
class Ghost;
class GameMode;
class GameObject;
class Interactable;
class Attemptable;
class Vent;
class GameScene : public Scene, public MinimapProvider, public std::enable_shared_from_this<GameScene>
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
	std::shared_ptr<Player>						m_Player;
	std::vector<std::shared_ptr<Ghost>>			m_arrGhosts;
	std::vector<std::shared_ptr<GameObject>>	m_arrGameObjects;
	std::vector<std::shared_ptr<Vent>>			m_arrVents;;

	std::set<Attemptable*>						m_setTasksLeft;

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
	const std::set<Attemptable*>& GetGameObjects() const override { return m_setTasksLeft; }

	void OnTaskSuccess();
	void OnTaskFail();

};