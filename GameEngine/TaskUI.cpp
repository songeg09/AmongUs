#include "pch.h"
#include "TaskUI.h"
#include "Texture.h"
#include "SceneManager.h"
#include "Button.h"

TaskUI::TaskUI()
{
	m_eTaskStatus = TASK_STATUS::PLAYING;
	m_pFrame = nullptr;
}

TaskUI::~TaskUI()
{
}

void TaskUI::Init(TEXTURE_TYPE _textureTypeFrame, std::function<void()> _funcOpenCallback, std::function<void()> _funcCloseCallback, std::function<void()> _funcSuccessCallback, std::function<void()> _funcFailCallback, std::function<void()> _funcBtnCloseCallback)
{
	UI::Init(_funcOpenCallback, _funcCloseCallback);
	m_funcSuccessCallback = _funcSuccessCallback;
	m_funcFailCallback = _funcFailCallback;

	m_pFrame = ResourceManager::GetInstance()->LoadTexture(_textureTypeFrame);
	m_vec2FrameStartPosInBackBuffer = SceneManager::GetInstance()->GetCurScene()->GetBackBufferSize();
	m_vec2FrameStartPosInBackBuffer.m_fx /= 2;
	m_vec2FrameStartPosInBackBuffer.m_fy /= 2;
	m_vec2FrameStartPosInBackBuffer.m_fx -= m_pFrame->GetWidth() / 2;
	m_vec2FrameStartPosInBackBuffer.m_fy -= m_pFrame->GetHeight() / 2;

	Vector2 RelativePos = m_vec2FrameStartPosInBackBuffer;
	RelativePos.m_fx -= ConstValue::fGameSceneGaurdBandPx;
	RelativePos.m_fy -= ConstValue::fGameSceneGaurdBandPx;
	RelativePos.m_fx /= ConstValue::vec2BaseWindowSize.m_fx;
	RelativePos.m_fy /= ConstValue::vec2BaseWindowSize.m_fy;
	RelativePos.m_fx -= 0.06;

	m_btnClose = new Button;
	m_btnClose->Init(TEXTURE_TYPE::BTN_X, RelativePos, UIElement::ANCHOR::TOP_LEFT, _funcBtnCloseCallback, true);
	m_arrUIElemetns.push_back(m_btnClose);
}

void TaskUI::Update()
{
	if (m_bVisibility == false)
		return;

	UI::Update();
	CheckWinStatus();
	switch (m_eTaskStatus)
	{
	case TASK_STATUS::PLAYING:
		return;
	case TASK_STATUS::SUCCESS:
		if (m_funcSuccessCallback != nullptr)
			m_funcSuccessCallback();
		return;
	case TASK_STATUS::FAIL:
		if (m_funcFailCallback != nullptr)
			m_funcFailCallback();
		return;
	}
}

void TaskUI::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	TransparentBlt(_memDC, m_vec2FrameStartPosInBackBuffer.m_fx, m_vec2FrameStartPosInBackBuffer.m_fy,
		m_pFrame->GetWidth(), m_pFrame->GetHeight(),
		m_pFrame->GetDC(),
		0, 0,
		m_pFrame->GetWidth(), m_pFrame->GetHeight(),
		RGB(255, 0, 255)
	);

	UI::Render(_memDC);
}
