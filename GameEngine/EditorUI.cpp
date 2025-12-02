#include "pch.h"
#include "EditorUI.h"
#include "Button.h"

EditorUI::EditorUI()
{
	m_btnPlayerStart = nullptr;
	m_btnWayPoints = nullptr;
	m_btnWallVertices = nullptr;
	m_btnVent = nullptr;
	m_btnDataUpload = nullptr;
	m_btnTimedButtons = nullptr;
	m_btnNumberSequence = nullptr;

	m_btnBacktoTitle = nullptr;
	m_btnSave = nullptr;
	m_btnRemoveLast = nullptr;
	m_btnClearSelected = nullptr;
}

EditorUI::~EditorUI()
{
}

void EditorUI::Init(std::function<void()> _funcPlayerStartBtnCallback, std::function<void()> _funcWayPointsBtnCallBack, std::function<void()> _funcWallVerticesBtnCallback, std::function<void()> _funcVentBtnCallback, std::function<void()> _funcDataUploadBtnCallback, std::function<void()> _funcTimedButtonsBtnCallback, std::function<void()> _funcNumberSequenceBtnCallback, std::function<void()> _funcBackToTitleCallback, std::function<void()> _funcSaveCallback, std::function<void()> _funcRemoveLastCallback, std::function<void()> _funcClearSelectedCallback)
{
	m_btnPlayerStart = new Button;
	m_btnWayPoints = new Button;
	m_btnWallVertices = new Button;
	m_btnVent = new Button;
	m_btnDataUpload = new Button;
	m_btnTimedButtons = new Button;
	m_btnNumberSequence = new Button;
	m_btnBacktoTitle = new Button;
	m_btnSave = new Button;
	m_btnRemoveLast = new Button;
	m_btnClearSelected = new Button;

	m_btnPlayerStart->Init(TEXTURE_TYPE::BTN_PLAYER_START, Vector2(0.1, 0.2), UIElement::ANCHOR::CENTER, _funcPlayerStartBtnCallback);
	m_btnWayPoints->Init(TEXTURE_TYPE::BTN_WAY_POINTS, Vector2(0.1, 0.3), UIElement::ANCHOR::CENTER, _funcWayPointsBtnCallBack);
	m_btnWallVertices->Init(TEXTURE_TYPE::BTN_WALL_VERTICES, Vector2(0.1, 0.4), UIElement::ANCHOR::CENTER, _funcWallVerticesBtnCallback);
	m_btnVent->Init(TEXTURE_TYPE::BTN_VENT, Vector2(0.1, 0.5), UIElement::ANCHOR::CENTER, _funcVentBtnCallback);
	m_btnDataUpload->Init(TEXTURE_TYPE::BTN_DATA_UPLOAD, Vector2(0.1, 0.6), UIElement::ANCHOR::CENTER, _funcDataUploadBtnCallback);
	m_btnTimedButtons->Init(TEXTURE_TYPE::BTN_TIMED_BUTTONS, Vector2(0.1, 0.7), UIElement::ANCHOR::CENTER, _funcTimedButtonsBtnCallback);
	m_btnNumberSequence->Init(TEXTURE_TYPE::BTN_NUMBER_SEQUENCE, Vector2(0.1, 0.8), UIElement::ANCHOR::CENTER, _funcNumberSequenceBtnCallback);
	m_btnBacktoTitle->Init(TEXTURE_TYPE::BTN_BACK_TO_TITLE, Vector2(0.9, 0.1), UIElement::ANCHOR::CENTER, _funcBackToTitleCallback);
	m_btnSave->Init(TEXTURE_TYPE::BTN_SAVE, Vector2(0.9, 0.2), UIElement::ANCHOR::CENTER, _funcSaveCallback);
	m_btnRemoveLast->Init(TEXTURE_TYPE::BTN_REMOVE_LAST, Vector2(0.9, 0.3), UIElement::ANCHOR::CENTER, _funcRemoveLastCallback);
	m_btnClearSelected->Init(TEXTURE_TYPE::BTN_CLEAR_SELECTED, Vector2(0.9, 0.9), UIElement::ANCHOR::CENTER, _funcClearSelectedCallback);

	m_arrUIElemetns.push_back(m_btnPlayerStart);
	m_arrUIElemetns.push_back(m_btnWayPoints);
	m_arrUIElemetns.push_back(m_btnWallVertices);
	m_arrUIElemetns.push_back(m_btnVent);
	m_arrUIElemetns.push_back(m_btnDataUpload);
	m_arrUIElemetns.push_back(m_btnTimedButtons);
	m_arrUIElemetns.push_back(m_btnNumberSequence);
	m_arrUIElemetns.push_back(m_btnBacktoTitle);
	m_arrUIElemetns.push_back(m_btnSave);
	m_arrUIElemetns.push_back(m_btnRemoveLast);
	m_arrUIElemetns.push_back(m_btnClearSelected);
}

void EditorUI::Render(HDC _memDC)
{
	UI::Render(_memDC);
}
