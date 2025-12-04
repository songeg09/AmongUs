#pragma once
#include "UI.h"

class Button;
class MenuUI : public UI
{
private:
	std::unique_ptr<Button> m_btnPlayAgain;
	std::unique_ptr<Button> m_btnQuit;
	
public:
	MenuUI();
	~MenuUI();

	void Init(std::function<void()> _funcPlayAgainCallback, std::function<void()> _funcQuitCallback);
	void Open() override;
	void Close() override;
};

