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
	Button*				m_btnClose;

	Vector2				m_vec2FrameStartPosInBackBuffer;
	Vector2				m_NumPadSize;
	Vector2				m_NumPadStartPosInBackBuffer;

public:
	NumberSequenceTask();
	~NumberSequenceTask();

	void Init(
		std::function<void()>	_funcOpenCallback,
		std::function<void()>	_funcCloseCallback,
		std::function<void()>	_SuccessCallback, 
		std::function<void()>	_FailCallback,
		std::function<void()> _BtnCloseCallback
	);
	void Render(HDC _memDC) override;

	void Reset();

	void Open() override;

private:
	void Swap(NumPadButton* btn1, NumPadButton* btn2);
};

