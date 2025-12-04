#pragma once
#include "UI.h"

class Button;
class ProgressBar;
class Player;
class GameMode;
class PlayerStatusUI : public UI
{
private:
	std::weak_ptr<GameMode>						m_GameMode;
	std::weak_ptr<Player>						m_Player;

	std::shared_ptr<Button>						m_btnUse;
	std::shared_ptr<Button>						m_btnMap;
	std::shared_ptr<Button>						m_btnSetting;
	std::shared_ptr<ProgressBar>				m_progressbarTasks;

public:
	PlayerStatusUI();
	~PlayerStatusUI();

	void Init(std::shared_ptr<GameMode> _GameMode, std::shared_ptr<Player> _Player, std::function<void()> _funcMapBtnCallback, std::function<void()> _funcMenuBtnCallback);
	void Update() override;
	void Render(HDC _memDC) override;

};

