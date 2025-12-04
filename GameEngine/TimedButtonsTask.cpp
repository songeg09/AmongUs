#include "pch.h"
#include "TimedButtonsTask.h"
#include "ResourceManager.h"
#include "Button.h"
#include "ProgressBar.h"
#include "TimingBar.h"

TimedButtonsTask::TimedButtonsTask()
{
}

TimedButtonsTask::~TimedButtonsTask()
{
}

void TimedButtonsTask::Init(
	std::function<void()>	_funcOpenCallback,
	std::function<void()>	_funcCloseCallback,
	std::function<void()>	_funcSuccessCallback,
	std::function<void()>	_funcFailCallback,
	std::function<void()>	_funcBtnCloseCallback
)
{
	TaskUI::Init(
		TEXTURE_TYPE::TASK_TIMED_BUTTONS_FRAME,
		_funcOpenCallback,
		_funcCloseCallback,
		_funcSuccessCallback,
		_funcFailCallback,
		_funcBtnCloseCallback
	);

	float y_gap = 0.21;
	for (int i = 0; i < 3; ++i)
	{
		m_btnButtons[i] = std::make_shared<Button>();
		m_btnButtons[i]->Init(
			TEXTURE_TYPE::TASK_TIMED_BUTTONS_BUTTON, 
			Vector2(0.62, 0.34 + y_gap * i), 
			UIElement::ANCHOR::CENTER,
			[this, i]() {m_TimingBars[i]->Stop(); }
		);
		UI::m_arrUIElemetns.push_back(m_btnButtons[i]);

		m_ProgressBars[i] = std::make_shared<ProgressBar>();
		m_ProgressBars[i]->Init(
			TEXTURE_TYPE::TASK_TIMED_BUTTONS_PROGRESSBAR_FRAME,
			TEXTURE_TYPE::TASK_TIMED_BUTTONS_PROGRESSBAR,
			Vector2(0.62, 0.29 + y_gap * i),
			UIElement::ANCHOR::CENTER
		);
		UI::m_arrUIElemetns.push_back(m_ProgressBars[i]);


		m_TimingBars[i] = std::make_shared<TimingBar>();
		if (i < 2)
		{
			m_TimingBars[i]->Init(
				TEXTURE_TYPE::TASK_TIMED_BUTTONS_TIMINGBAR,
				TEXTURE_TYPE::TASK_TIMED_BUTTONS_TIMINGCURSOR,
				Vector2(0.38, 0.29 + y_gap * i),
				UIElement::ANCHOR::CENTER,
				[this,i]() {
					m_btnButtons[i]->SetActivate(false);
					m_btnButtons[i + 1]->SetActivate(true); 
					m_TimingBars[i + 1]->Start();
				},
				[this]() {m_eTaskStatus = TASK_STATUS::FAIL; }
			);
		}
		else
		{
			m_TimingBars[i]->Init(
				TEXTURE_TYPE::TASK_TIMED_BUTTONS_TIMINGBAR,
				TEXTURE_TYPE::TASK_TIMED_BUTTONS_TIMINGCURSOR,
				Vector2(0.38, 0.29 + y_gap * i),
				UIElement::ANCHOR::CENTER,
				[this]() {m_eTaskStatus = TASK_STATUS::SUCCESS; },
				[this]() {m_eTaskStatus = TASK_STATUS::FAIL; }
			);
		}
		UI::m_arrUIElemetns.push_back(m_TimingBars[i]);
	}
}

void TimedButtonsTask::Update()
{
	if (m_bVisibility == false)
		return;

	for (int i = 0; i < 3; ++i)
		m_ProgressBars[i]->SetProgress(easing::EaseInOutBounce(m_TimingBars[i]->GetRatio()));

	TaskUI::Update();
}


void TimedButtonsTask::Reset()
{
	m_eTaskStatus = TASK_STATUS::PLAYING;
	for (int i = 0; i < 3; ++i)
	{
		m_btnButtons[i]->SetActivate(false);
		m_TimingBars[i]->Reset();
		m_TimingBars[i]->SetCycleTime((float)(rand() % 1000 / 1000) + 1.0f);
	}
	m_btnButtons[0]->SetActivate(true);
	m_TimingBars[0]->Start();
}

void TimedButtonsTask::CheckWinStatus()
{
}


