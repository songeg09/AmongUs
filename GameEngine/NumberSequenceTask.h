#pragma once
#include "TaskUI.h"

class Texture;
class NumPadButton;
class Button;
class NumberSequenceTask : public TaskUI
{
private:
	Texture*			m_pFrame;

	NumPadButton*		m_arrNumPadBtns[10];

	Vector2				m_NumPadSize;
	Vector2				m_NumPadStartPosInBackBuffer;

	int					m_NextBtnIndex;
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
	void Open() override;
	void CheckWinStatus() override;

private:
	void Swap(NumPadButton* btn1, NumPadButton* btn2);
};

