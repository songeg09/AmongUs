#include "pch.h"
#include "NumberSequenceTask.h"
#include "Button.h"

NumberSequenceTask::NumberSequenceTask()
{
	for (int i = 0; i < 10; ++i)
		m_arrBtns[i] = nullptr;
	m_btnClose = nullptr;
}

NumberSequenceTask::~NumberSequenceTask()
{
}

void NumberSequenceTask::Init(std::function<void()> _SuccessCallback, std::function<void()> _FailCallback, std::function<void()> _BtnCloseCallback)
{
	TaskUI::Init(_SuccessCallback, _FailCallback);
	m_btnClose = new Button;
	m_btnClose->Init(TEXTURE_TYPE::BTN_X, Vector2(0.15,0.15), UIElement::ANCHOR::CENTER, _BtnCloseCallback);
	m_arrUIElemetns.push_back(m_btnClose);
}
