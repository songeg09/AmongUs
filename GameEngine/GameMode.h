#pragma once
class Player;

class GameMode
{
private:
	Player*			m_Player;

	int				m_iTotalTasks;
	int				m_iCompletedTasks;

	Flags			m_UIFlags;

public:
	GameMode();
	~GameMode();

	void Init(Player* _Player);

	void OpenUI(int _uiIndex);
	float GetProgress() { return (float)m_iCompletedTasks / (float)m_iTotalTasks; }
	
	Flags GetUIFlag() {return m_UIFlags;}
};

