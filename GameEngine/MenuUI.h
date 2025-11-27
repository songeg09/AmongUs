#pragma once
#include "UI.h"

class Button;
class MenuUI : public UI
{
private:
	Button* m_btnPlayAgain;
	Button* m_btnQuit;
	
public:
	MenuUI();
	~MenuUI();

	void Init(std::function<void()> _funcPlayAgainCallback, std::function<void()> _funcQuitCallback);
	void Open() override;
	void Close() override;
};

