#pragma once
class IMinimapProvider;
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
	std::weak_ptr<Player>				m_Player;
	std::weak_ptr<IMinimapProvider>		m_MinimapProvider;
	int									m_iTotalTasks;
	GAME_STATE							m_eState;

public:
	GameMode();
	~GameMode();

	void Init(std::shared_ptr<Player> _Player, std::shared_ptr<IMinimapProvider> _MinimapProvider);
	void Update();
	float GetProgress();
	GAME_STATE GetGameState() { return m_eState; }
};

