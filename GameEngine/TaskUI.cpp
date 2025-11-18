#include "pch.h"
#include "TaskUI.h"

TaskUI::TaskUI()
{
}

TaskUI::~TaskUI()
{
}

void TaskUI::Init(std::function<void()> _funcOpenCallback, std::function<void()> _funcCloseCallback, std::function<void()> _SuccessCallback, std::function<void()> _FailCallback)
{
	UI::Init(_funcOpenCallback, _funcCloseCallback);
	m_SuccessCallback = _SuccessCallback;
	m_FailCallback = _FailCallback;
}
