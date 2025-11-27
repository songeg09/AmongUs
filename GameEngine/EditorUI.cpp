#include "pch.h"
#include "EditorUI.h"
#include "Button.h"

EditorUI::EditorUI()
{
	m_btnPlayerStart = nullptr;
	m_btnWayPoints = nullptr;
	m_btnWallVertices = nullptr;
	m_btnDataUpload = nullptr;
	m_btnTimedButtons = nullptr;
	m_btnNumberSequence = nullptr;
}

EditorUI::~EditorUI()
{
}

void EditorUI::Init(std::function<void()> _funcPlayerStartBtnCallback, std::function<void()> _funcWayPointsBtnCallBack, std::function<void()> _funcWallVerticesBtnCallback, std::function<void()> _funcDataUploadBtnCallback, std::function<void()> _funcTimedButtonsBtnCallback, std::function<void()> _funcNumberSequenceBtnCallback)
{
	m_btnPlayerStart = new Button;
	m_btnWayPoints = new Button;
	m_btnWallVertices = new Button;
	m_btnDataUpload = new Button;
	m_btnTimedButtons = new Button;
	m_btnNumberSequence = new Button;

	m_btnPlayerStart->Init(TEXTURE_TYPE::BTN_PLAYER_START, Vector2(0.1,0.2), UIElement::ANCHOR::CENTER, _funcPlayerStartBtnCallback);
	m_btnWayPoints->Init(TEXTURE_TYPE::BTN_WAY_POINTS, Vector2(0.1, 0.3), UIElement::ANCHOR::CENTER, _funcWayPointsBtnCallBack);
	m_btnWallVertices->Init(TEXTURE_TYPE::BTN_WALL_VERTICES, Vector2(0.1, 0.4), UIElement::ANCHOR::CENTER, _funcWallVerticesBtnCallback);
	m_btnDataUpload->Init(TEXTURE_TYPE::BTN_DATA_UPLOAD, Vector2(0.1, 0.5), UIElement::ANCHOR::CENTER, _funcDataUploadBtnCallback);
	m_btnTimedButtons->Init(TEXTURE_TYPE::BTN_TIMED_BUTTONS, Vector2(0.1, 0.6), UIElement::ANCHOR::CENTER, _funcTimedButtonsBtnCallback);
	m_btnNumberSequence->Init(TEXTURE_TYPE::BTN_NUMBER_SEQUENCE, Vector2(0.1, 0.7), UIElement::ANCHOR::CENTER, _funcNumberSequenceBtnCallback);

	m_arrUIElemetns.push_back(m_btnPlayerStart);
	m_arrUIElemetns.push_back(m_btnWayPoints);
	m_arrUIElemetns.push_back(m_btnWallVertices);
	m_arrUIElemetns.push_back(m_btnDataUpload);
	m_arrUIElemetns.push_back(m_btnTimedButtons);
	m_arrUIElemetns.push_back(m_btnNumberSequence);
}

void EditorUI::Render(HDC _memDC)
{
	UI::Render(_memDC);
}
