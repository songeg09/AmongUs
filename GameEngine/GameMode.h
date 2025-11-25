#pragma once
class MinimapProvider;
class Player;
class GameMode
{
public:
	enum GAME_STATE
	{
		PLAYING,
		LOSE,
		WIN
	};

private:
	Player*				m_Player;
	MinimapProvider*	m_MinimapProvider;
	int					m_iTotalTasks;
	GAME_STATE			m_eState;

public:
	GameMode();
	~GameMode();

	void Init(Player* _Player, MinimapProvider* _MinimapProvider);
	void Update();
	float GetProgress();
	GAME_STATE GetGameState() { return m_eState; }
};

