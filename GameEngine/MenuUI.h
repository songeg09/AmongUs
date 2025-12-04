#pragma once
#include "UI.h"

class Button;
class MenuUI : public UI
{
private:
	std::shared_ptr<Button> m_btnPlayAgain;
	std::shared_ptr<Button> m_btnQuit;
	
public:
	MenuUI();
	~MenuUI();

	void Init(std::function<void()> _funcPlayAgainCallback, std::function<void()> _funcQuitCallback);
	void Open() override;
	void Close() override;
};

