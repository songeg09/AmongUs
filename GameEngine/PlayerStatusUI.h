#pragma once
#include "UI.h"

class Button;
class ProgressBar;
class Player;
class GameMode;
class PlayerStatusUI : public UI
{
private:
	GameMode*		m_GameMode;
	Player*			m_Player;

	Button*			m_btnUse;
	Button*			m_btnMap;
	Button*			m_btnSetting;
	ProgressBar*	m_progressbarTasks;

public:
	PlayerStatusUI();
	~PlayerStatusUI();

	void Init(GameMode* _GameMode, Player* _Player, std::function<void()> _mapBtnCallback);
	void Update() override;
	void Render(HDC _memDC) override;

};

