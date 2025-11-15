#pragma once
#include "UI.h"

class Button;
class ProgressBar;
class GameMode;
class Player;
class PlayerHUD : public UI
{
private:
	GameMode*		m_GameMode;
	Player*			m_Player;

	Button*			m_btnUse;
	Button*			m_btnMap;
	Button*			m_btnSetting;
	ProgressBar*	m_progressbarTasks;
	

public:
	PlayerHUD();
	~PlayerHUD();

	void Init(GameMode* _GameMode, Player* _Player);
	void Update() override;
	void Render(HDC _memDC) override;

private:

};

