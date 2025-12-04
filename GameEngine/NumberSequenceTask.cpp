#include "pch.h"
#include "NumberSequenceTask.h"
#include "ResourceManager.h"
#include "Button.h"
#include "SceneManager.h"
#include "Texture.h"

NumberSequenceTask::NumberSequenceTask()
{
	m_NextBtnIndex = 0;
}

NumberSequenceTask::~NumberSequenceTask()
{
}

void NumberSequenceTask::Init(std::function<void()> _funcOpenCallback, std::function<void()> _funcCloseCallback, std::function<void()> _SuccessCallback, std::function<void()> _FailCallback, std::function<void()> _BtnCloseCallback)
{
	TaskUI::Init(
		TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_FRAME, 
		_funcOpenCallback, 
		_funcCloseCallback, 
		_SuccessCallback, 
		_FailCallback, 
		_BtnCloseCallback
	);

	Texture* NumPad = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_NUMBER_START);
	Vector2 m_NumPadSize = Vector2(NumPad->GetWidth(), NumPad->GetHeight());
	m_NumPadSize.m_fx /= ConstValue::vec2BaseWindowSize.m_fx;
	m_NumPadSize.m_fy /= ConstValue::vec2BaseWindowSize.m_fy;

	Vector2 m_NumPadStartPosInBackBuffer = m_vec2FrameStartPosInBackBuffer;
	m_NumPadStartPosInBackBuffer.m_fx += 40;
	m_NumPadStartPosInBackBuffer.m_fy += 40;
	m_NumPadStartPosInBackBuffer.m_fx -= ConstValue::fGameSceneGaurdBandPx;
	m_NumPadStartPosInBackBuffer.m_fy -= ConstValue::fGameSceneGaurdBandPx;
	m_NumPadStartPosInBackBuffer.m_fx /= ConstValue::vec2BaseWindowSize.m_fx;
	m_NumPadStartPosInBackBuffer.m_fy /= ConstValue::vec2BaseWindowSize.m_fy;

	int btnIndex = 0;
	Vector2 vec2NumPadPos;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			btnIndex = 5 * i + j;
			vec2NumPadPos.m_fx = m_NumPadStartPosInBackBuffer.m_fx + m_NumPadSize.m_fx * j;
			vec2NumPadPos.m_fy = m_NumPadStartPosInBackBuffer.m_fy + m_NumPadSize.m_fy * i;

			m_arrNumPadBtns[btnIndex] = std::make_unique<Button>();
			m_arrNumPadBtns[btnIndex]->Init(
				(TEXTURE_TYPE)(btnIndex + TEXTURE_TYPE::TASK_NUMBER_SEQUENCE_NUMBER_START),
				vec2NumPadPos,
				UIElement::ANCHOR::TOP_LEFT,
				std::bind(&Button::SetActivate, m_arrNumPadBtns[btnIndex].get(), false)
			);
			m_arrUIElemetns.push_back(m_arrNumPadBtns[btnIndex].get());
		}
	}
	Reset();
}

void NumberSequenceTask::Reset()
{
	m_eTaskStatus = TASK_STATUS::PLAYING;
	m_NextBtnIndex = 0;

	for (std::unique_ptr<Button>& numPadBtn : m_arrNumPadBtns)
	{
		numPadBtn->SetActivate(true);
	}

	int a, b;
	for (int i = 0; i < 20; ++i)
	{
		a = rand() % 10;
		b = rand() % 10;
		Swap(m_arrNumPadBtns[a].get(), m_arrNumPadBtns[b].get());
	}
}

void NumberSequenceTask::Swap(Button* btn1, Button* btn2)
{
	Vector2 temp = btn1->GetRelativePos();
	btn1->SetRelativePos(btn2->GetRelativePos());
	btn2->SetRelativePos(temp);

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
	for (std::unique_ptr<Button>& btn : m_arrNumPadBtns)
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
