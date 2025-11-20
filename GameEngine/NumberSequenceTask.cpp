#include "pch.h"
#include "NumberSequenceTask.h"
#include "ResourceManager.h"
#include "Button.h"
#include "NumPadButton.h"
#include "SceneManager.h"
#include "Texture.h"

NumberSequenceTask::NumberSequenceTask()
{
	for (int i = 0; i < 10; ++i)
		m_arrNumPadBtns[i] = nullptr;
	m_btnClose = nullptr;
	m_pFrame = nullptr;
}

NumberSequenceTask::~NumberSequenceTask()
{
}

void NumberSequenceTask::Init(std::function<void()> _funcOpenCallback, std::function<void()> _funcCloseCallback, std::function<void()> _SuccessCallback, std::function<void()> _FailCallback, std::function<void()> _BtnCloseCallback)
{
	TaskUI::Init(TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_FRAME, _funcOpenCallback, _funcCloseCallback, _SuccessCallback, _FailCallback, _BtnCloseCallback);

	Texture* NumPad = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_NUMBER_START);
	m_NumPadSize = Vector2(NumPad->GetWidth(), NumPad->GetHeight());
	m_NumPadStartPosInBackBuffer = m_vec2FrameStartPosInBackBuffer;
	m_NumPadStartPosInBackBuffer.m_fx += 40;
	m_NumPadStartPosInBackBuffer.m_fy += 40;

	int btnIndex = 0;
	Vector2 vec2NumPadPos;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			btnIndex = 5 * i + j;
			vec2NumPadPos.m_fx = m_NumPadStartPosInBackBuffer.m_fx + m_NumPadSize.m_fx * j;
			vec2NumPadPos.m_fy = m_NumPadStartPosInBackBuffer.m_fy + m_NumPadSize.m_fy * i;

			m_arrNumPadBtns[btnIndex] = new NumPadButton;
			m_arrNumPadBtns[btnIndex]->Init(
				(TEXTURE_TYPE)(btnIndex + TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_NUMBER_START),
				vec2NumPadPos,
				UIElement::ANCHOR::TOP_LEFT,
				std::bind(&Button::SetActivate, m_arrNumPadBtns[btnIndex], false)
			);
			m_arrUIElemetns.push_back(m_arrNumPadBtns[btnIndex]);
		}
	}
	Reset();
}

void NumberSequenceTask::Reset()
{
	m_eTaskStatus = TASK_STATUS::PLAYING;
	m_NextBtnIndex = 0;

	for (NumPadButton* numPadBtn : m_arrNumPadBtns)
	{
		numPadBtn->SetActivate(true);
	}

	int a, b;
	for (int i = 0; i < 20; ++i)
	{
		a = rand() % 10;
		b = rand() % 10;
		Swap(m_arrNumPadBtns[a], m_arrNumPadBtns[b]);
	}
}

void NumberSequenceTask::Open()
{
	Reset();
	UI::Open();
}

void NumberSequenceTask::Swap(NumPadButton* btn1, NumPadButton* btn2)
{
	Vector2 temp = btn1->GetAbsoluteStartPos();
	btn1->SetAbsoluteStartpos(btn2->GetAbsoluteStartPos());
	btn2->SetAbsoluteStartpos(temp);

	btn1->SetBtnArea();
	btn2->SetBtnArea();
}

void NumberSequenceTask::CheckWinStatus()
{
	if (m_NextBtnIndex == 10)
	{
		m_eTaskStatus = TASK_STATUS::SUCCESS;
		return;
	}
	
	int NumOfDeactivatedButtons = 0;
	for (NumPadButton* btn : m_arrNumPadBtns)
	{
		if (!btn->IsActivate())
			NumOfDeactivatedButtons++;
	}

	if (NumOfDeactivatedButtons == m_NextBtnIndex)
		m_eTaskStatus = TASK_STATUS::PLAYING;
	else if(!m_arrNumPadBtns[m_NextBtnIndex]->IsActivate())
	{
		m_eTaskStatus = TASK_STATUS::PLAYING;
		m_NextBtnIndex++;
	}
	else
	{
		m_eTaskStatus = TASK_STATUS::FAIL;
	}
}
