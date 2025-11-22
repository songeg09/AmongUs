#pragma once
#include "TaskUI.h"

class Button;
class ProgressBar;
class TimingBar;
class TimedButtonsTask : public TaskUI
{
private:
	Button*			m_btnButtons[3];
	ProgressBar*	m_ProgressBars[3];
	TimingBar*		m_TimingBars[3];
	
public:
	TimedButtonsTask();
	~TimedButtonsTask();

	void Init(
		std::function<void()>	_funcOpenCallback,
		std::function<void()>	_funcCloseCallback,
		std::function<void()>	_funcSuccessCallback,
		std::function<void()>	_funcFailCallback,
		std::function<void()>	_funcBtnCloseCallback
	);
	void Update() override;

	void Reset() override;
	void CheckWinStatus() override;
	void Open() override;
};

