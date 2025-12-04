#pragma once
#include "TaskUI.h"

class Texture;
class Button;
class NumberSequenceTask : public TaskUI
{
private:
	std::unique_ptr<Button>				m_arrNumPadBtns[10];
	int									m_NextBtnIndex;

public:
	NumberSequenceTask();
	~NumberSequenceTask();

	void Init(
		std::function<void()>	_funcOpenCallback,
		std::function<void()>	_funcCloseCallback,
		std::function<void()>	_SuccessCallback, 
		std::function<void()>	_FailCallback,
		std::function<void()>	_BtnCloseCallback
	);

	void Reset() override;
	void CheckWinStatus() override;

private:
	void Swap(Button* btn1, Button* btn2);
};

