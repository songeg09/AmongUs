#pragma once
class GameMode
{
private:

	int				m_iTotalTasks;
	int				m_iCompletedTasks;

public:
	GameMode();
	~GameMode();

	void Init();
	float GetProgress() { return (float)m_iCompletedTasks / (float)m_iTotalTasks; }
};

