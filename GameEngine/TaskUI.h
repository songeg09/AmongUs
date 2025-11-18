#pragma once
#include "UI.h"

class TaskUI : public UI
{
protected:
	std::function<void()>	m_SuccessCallback;
	std::function<void()>	m_FailCallback;

public:
	TaskUI();
	~TaskUI();

	void Init(std::function<void()> _SuccessCallback, std::function<void()> _FailCallback);
};

