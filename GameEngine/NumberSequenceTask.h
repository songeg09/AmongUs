#pragma once
#include "TaskUI.h"

class Button;
class NumberSequenceTask : public TaskUI
{
private:
	Button* m_arrBtns[10];
	Button* m_btnClose;

public:
	NumberSequenceTask();
	~NumberSequenceTask();

	void Init(std::function<void()> _SuccessCallback, std::function<void()> _FailCallback, std::function<void()> _BtnCloseCallback);
};

