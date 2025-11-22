#pragma once
class MinimapProvider;
class GameMode
{
private:
	MinimapProvider*	m_MinimapProvider;
	int					m_iTotalTasks;

public:
	GameMode();
	~GameMode();

	void Init(MinimapProvider* _MinimapProvider);
	void Update();
	float GetProgress();
};

