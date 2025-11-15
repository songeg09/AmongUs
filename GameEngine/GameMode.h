#pragma once
class Player;
class GameScene;
class GameMode
{
private:
	Player*			m_Player;
	GameScene*		m_GameScene;

	int				m_iTotalTasks;
	int				m_iCompletedTasks;

public:
	GameMode();
	~GameMode();

	void Init(Player* _Player, GameScene* _GameScene,  int _iTotalTasks);

	void ChangeUI(int _uiIndex);
	float GetProgress() { return (float)m_iCompletedTasks / (float)m_iTotalTasks; }

	void OpenMapUI();
	void OpenHUDUI();
};

