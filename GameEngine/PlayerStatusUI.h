#pragma once
#include "UI.h"

class Button;
class ProgressBar;
class Player;
class GameMode;
class PlayerStatusUI : public UI
{
private:
	GameMode*						m_GameMode;
	Player*							m_Player;

	std::shared_ptr<Button>			m_btnUse;
	std::shared_ptr<Button>			m_btnMap;
	std::shared_ptr<Button>			m_btnSetting;
	std::shared_ptr<ProgressBar>	m_progressbarTasks;

public:
	PlayerStatusUI();
	~PlayerStatusUI();

	void Init(GameMode* _GameMode, Player* _Player, std::function<void()> _funcMapBtnCallback, std::function<void()> _funcMenuBtnCallback);
	void Update() override;
	void Render(HDC _memDC) override;

};

