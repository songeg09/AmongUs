#include "pch.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "InputManager.h"
#include "EditorUI.h"
#include "Core.h"
#include "SceneManager.h"
#include "GDIManager.h"

EditorScene::EditorScene(std::wstring _strName)
	:Scene(_strName)
{
	m_eCurSelected = SELECTED::PLAYER_START;
	m_bUIClicked = false;
}

EditorScene::~EditorScene()
{
}

void EditorScene::Init()
{
	Scene::Init();

	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);

	ConfigureRenderSurface(
		Vector2(m_pBackGround.lock()->GetWidth(), m_pBackGround.lock()->GetHeight()),
		ConstValue::fGameSceneGaurdBandPx
	);

	// UI »ý¼º
	m_arrUIs.resize(static_cast<int>(UI_TYPE::END));
	std::unique_ptr<EditorUI> editorUI = std::make_unique<EditorUI>();
	editorUI->Init(
		std::bind(&EditorScene::ChangeSelected, this, SELECTED::PLAYER_START),
		std::bind(&EditorScene::ChangeSelected, this, SELECTED::WAY_POINTS),
		std::bind(&EditorScene::ChangeSelected, this, SELECTED::WALL_VERTICES),
		std::bind(&EditorScene::ChangeSelected, this, SELECTED::VENT),
		std::bind(&EditorScene::ChangeSelected, this, SELECTED::DATA_UPLOAD),
		std::bind(&EditorScene::ChangeSelected, this, SELECTED::TIMED_BUTTONS),
		std::bind(&EditorScene::ChangeSelected, this, SELECTED::NUMBER_SEQUNECE),
		std::bind(&EditorScene::BacktoTitle, this),
		std::bind(&EditorScene::Save, this),
		std::bind(&EditorScene::RemoveLast, this),
		std::bind(&EditorScene::ClearSelected, this)
	);
	m_arrUIs[static_cast<int>(UI_TYPE::EDITOR)] = std::move(editorUI);
	m_UIFlags = Flag(static_cast<int>(UI_TYPE::EDITOR));

	m_eCurSelected = SELECTED::PLAYER_START;
	m_bUIClicked = false;
	m_vec2CurPos = { (float)m_pBackGround.lock()->GetWidth() / 2.0f, (float)m_pBackGround.lock()->GetHeight() / 2.0f };

	m_MapInfo.Load();
}

void EditorScene::Release()
{
	m_arrCurWallVertices.clear();
	Scene::Release();
}

void EditorScene::Update()
{
	Move();
	m_bUIClicked = false;
	Scene::Update();
	InputCheck();
}

void EditorScene::Render(HDC _memDC)
{
	Vector2 BackBufferTopLeftInScene = GetBackBufferTopLeftInScene();
	BitBlt(_memDC, 0, 0, m_vec2BackBufferSize.m_fx, m_vec2BackBufferSize.m_fy,
		m_pBackGround.lock()->GetDC(), BackBufferTopLeftInScene.m_fx, BackBufferTopLeftInScene.m_fy, SRCCOPY);
	DrawObjects(_memDC);
	PrintSelected(_memDC);
	Scene::Render(_memDC);
}



Vector2 EditorScene::GetBackBufferTopLeftInScene()
{
	Vector2 vec2BackBufferTopLeft = GetViewPortTopLeftInScene();
	vec2BackBufferTopLeft.m_fx -= m_fGuardBandPx;
	vec2BackBufferTopLeft.m_fy -= m_fGuardBandPx;

	return vec2BackBufferTopLeft;
}

Vector2 EditorScene::GetViewPortTopLeftInScene()
{
	Vector2 vec2TopLeftInScene = m_vec2CurPos;
	vec2TopLeftInScene.m_fx -= ConstValue::vec2BaseWindowSize.m_fx / 2;
	vec2TopLeftInScene.m_fy -= ConstValue::vec2BaseWindowSize.m_fy / 2;

	return vec2TopLeftInScene;
}

void EditorScene::Move()
{
	Vector2 vec2MoveForce;
	if (InputManager::GetInstance()->GetKeyState('A') == KEY_STATE::PRESS)
		vec2MoveForce.m_fx += -1.0f;
	if (InputManager::GetInstance()->GetKeyState('D') == KEY_STATE::PRESS)
		vec2MoveForce.m_fx += 1.0f;
	if (InputManager::GetInstance()->GetKeyState('W') == KEY_STATE::PRESS)
		vec2MoveForce.m_fy += -1.0f;
	if (InputManager::GetInstance()->GetKeyState('S') == KEY_STATE::PRESS)
		vec2MoveForce.m_fy += 1.0f;

	if (vec2MoveForce.isValid() == true)
	{
		m_vec2CurPos += vec2MoveForce;
		m_vec2CurPos.m_fx = std::clamp(m_vec2CurPos.m_fx, ConstValue::vec2BaseWindowSize.m_fx * 0.5f, m_vec2SceneSize.m_fx - ConstValue::vec2BaseWindowSize.m_fx * 0.5f);
		m_vec2CurPos.m_fy = std::clamp(m_vec2CurPos.m_fy, ConstValue::vec2BaseWindowSize.m_fy * 0.5f, m_vec2SceneSize.m_fy - ConstValue::vec2BaseWindowSize.m_fy * 0.5f);
	}	
}

void EditorScene::InputCheck()
{
	if (m_bUIClicked)
		return;

	POINT m_ptMouse;
	GetCursorPos(&m_ptMouse);
	ScreenToClient(Core::GetInstance()->GethWnd(), &m_ptMouse);

	static RECT clickableArea = {0,0,ConstValue::vec2BaseWindowSize.m_fx,ConstValue::vec2BaseWindowSize.m_fy,};

	if (!(PtInRect(&clickableArea, m_ptMouse) && InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_STATE::DOWN))
		return;

	PlaceObject(Vector2(m_ptMouse.x, m_ptMouse.y));
}

void EditorScene::PrintSelected(HDC _memDC)
{
	static Vector2 Pos = { m_fGuardBandPx + ConstValue::vec2BaseWindowSize.m_fx * 0.1f , m_fGuardBandPx + ConstValue::vec2BaseWindowSize.m_fy * 0.1f };

	std::wstring msg = std::format(L"Selected: {}", GetSelectedString());
	TextOutW(_memDC, Pos.m_fx, Pos.m_fy, msg.c_str(), msg.length());
}

void EditorScene::DrawObjects(HDC _memDC)
{
	Vector2 BackBufferTopLeftInScene = GetBackBufferTopLeftInScene();
	
	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	
	// Player Start
	GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::GREEN);
	DrawObject(_memDC, BackBufferTopLeftInScene, m_MapInfo.m_vec2PlayerStart, ConstValue::vec2PlayerStartSize);

	// Way Points
	GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::RED);
	for (const Vector2& waypoint : m_MapInfo.m_arrWayPoints)
		DrawObject(_memDC, BackBufferTopLeftInScene, waypoint, ConstValue::vec2WayPointSize);

	// Objects (Vent & Tasks) + Wall
	GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);
	for (int i = 0; i < m_MapInfo.m_arrAllWallVertices.size(); ++i)
		for (int j = 0; j < m_MapInfo.m_arrAllWallVertices[i].size() - 1; ++j)
			DrawLine(_memDC, BackBufferTopLeftInScene, m_MapInfo.m_arrAllWallVertices[i][j], m_MapInfo.m_arrAllWallVertices[i][j + 1]);

	for (int i = 1; i < m_arrCurWallVertices.size(); ++i)
		DrawLine(_memDC, BackBufferTopLeftInScene, m_arrCurWallVertices[i - 1], m_arrCurWallVertices[i]);

	for (const Vector2& vent : m_MapInfo.m_arrVent)
		DrawObject(_memDC, BackBufferTopLeftInScene, vent, ConstValue::vec2VentSize);

	for (const Vector2& timedButton : m_MapInfo. m_arrTimedButtonsPos)
		DrawObject(_memDC, BackBufferTopLeftInScene, timedButton, ConstValue::vec2TaskSize);

	for (const Vector2& dataUpload : m_MapInfo.m_arrDataUploadPos)
		DrawObject(_memDC, BackBufferTopLeftInScene, dataUpload, ConstValue::vec2TaskSize);

	for (const Vector2& numberSequence : m_MapInfo.m_arrNumberSequencePos)
		DrawObject(_memDC, BackBufferTopLeftInScene, numberSequence, ConstValue::vec2TaskSize);


	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}

void EditorScene::DrawObject(HDC _memDC, Vector2 _BackBufferTopLeftInScene, Vector2 Pos, Vector2 _Size)
{
	Rectangle(_memDC,
		Pos.m_fx - _BackBufferTopLeftInScene.m_fx - _Size.m_fx / 2.0f,
		Pos.m_fy - _BackBufferTopLeftInScene.m_fy - _Size.m_fy / 2.0f,
		Pos.m_fx - _BackBufferTopLeftInScene.m_fx + _Size.m_fx / 2.0f,
		Pos.m_fy - _BackBufferTopLeftInScene.m_fy + _Size.m_fy / 2.0f
	);
}

void EditorScene::DrawLine(HDC _memDC, Vector2 _BackBufferTopLeftInScene, Vector2 StartPos, Vector2 EndPos)
{
	MoveToEx(_memDC, StartPos.m_fx - _BackBufferTopLeftInScene.m_fx, StartPos.m_fy - _BackBufferTopLeftInScene.m_fy, nullptr);
	LineTo(_memDC, EndPos.m_fx - _BackBufferTopLeftInScene.m_fx, EndPos.m_fy - _BackBufferTopLeftInScene.m_fy);
}


std::wstring EditorScene::GetSelectedString()
{
	switch (m_eCurSelected)
	{
	case SELECTED::PLAYER_START:
		return L"Player Start";
	case SELECTED::WAY_POINTS:
		return L"Way Points";
	case SELECTED::WALL_VERTICES:
		return L"Wall Vertices";
	case SELECTED::VENT:
		return L"Vent";
	case SELECTED::TIMED_BUTTONS:
		return L"Timed Buttons";
	case SELECTED::DATA_UPLOAD:
		return L"Data Upload";
	case SELECTED::NUMBER_SEQUNECE:
		return L"Number Sequence";
	}
}

void EditorScene::PlaceObject(Vector2 _vec2Pos)
{
	Vector2 AbsolutePos = GetViewPortTopLeftInScene() + _vec2Pos;

	switch (m_eCurSelected)
	{
	case SELECTED::PLAYER_START:
		m_MapInfo.m_vec2PlayerStart = AbsolutePos;
		break;
	case SELECTED::WAY_POINTS:
		m_MapInfo.m_arrWayPoints.push_back(AbsolutePos);
		break;
	case SELECTED::VENT:
		m_MapInfo.m_arrVent.push_back(AbsolutePos);
		break;
	case SELECTED::WALL_VERTICES:
		if (m_arrCurWallVertices.size()>=3 && Vector2::Distance(m_arrCurWallVertices[0], AbsolutePos) <= ConstValue::fWallVerticesThreshold)
		{
			m_arrCurWallVertices.push_back(m_arrCurWallVertices[0]);
			m_MapInfo.m_arrAllWallVertices.push_back(m_arrCurWallVertices);
			m_arrCurWallVertices.clear();
		}
		else
			m_arrCurWallVertices.push_back(AbsolutePos);
		break;
	case SELECTED::TIMED_BUTTONS:
		m_MapInfo.m_arrTimedButtonsPos.push_back(AbsolutePos);
		break;
	case SELECTED::DATA_UPLOAD:
		m_MapInfo.m_arrDataUploadPos.push_back(AbsolutePos);
		break;
	case SELECTED::NUMBER_SEQUNECE:
		m_MapInfo.m_arrNumberSequencePos.push_back(AbsolutePos);
		break;
	}
}

void EditorScene::ChangeSelected(SELECTED _eNewSelected)
{
	m_eCurSelected = _eNewSelected;
	m_bUIClicked = true;
}

void EditorScene::RemoveLast()
{
	switch (m_eCurSelected)
	{
	case SELECTED::PLAYER_START:
		m_MapInfo.m_vec2PlayerStart = { -1,-1 };
		break;
	case SELECTED::WAY_POINTS:
		if(!m_MapInfo.m_arrWayPoints.empty())
			m_MapInfo.m_arrWayPoints.pop_back();
		break;
	case SELECTED::VENT:
		if (!m_MapInfo.m_arrVent.empty())
			m_MapInfo.m_arrVent.pop_back();
		break;
	case SELECTED::WALL_VERTICES:
		if (!m_arrCurWallVertices.empty())
			m_arrCurWallVertices.pop_back();
		else if (!m_MapInfo.m_arrAllWallVertices.empty())
			m_MapInfo.m_arrAllWallVertices.pop_back();
		break;
	case SELECTED::TIMED_BUTTONS:
		if (!m_MapInfo.m_arrTimedButtonsPos.empty())
			m_MapInfo.m_arrTimedButtonsPos.pop_back();
		break;
	case SELECTED::DATA_UPLOAD:
		if (!m_MapInfo.m_arrDataUploadPos.empty())
			m_MapInfo.m_arrDataUploadPos.pop_back();
		break;
	case SELECTED::NUMBER_SEQUNECE:
		if (!m_MapInfo.m_arrNumberSequencePos.empty())
			m_MapInfo.m_arrNumberSequencePos.pop_back();
		break;
	}
	m_bUIClicked = true;
}

void EditorScene::Save()
{
	m_MapInfo.Save();
	m_bUIClicked = true;
}

void EditorScene::ClearSelected()
{
	switch (m_eCurSelected)
	{
	case SELECTED::PLAYER_START:
		m_MapInfo.m_vec2PlayerStart = { -1,-1 };
		break;
	case SELECTED::WAY_POINTS:
		m_MapInfo.m_arrWayPoints.clear();
		break;
	case SELECTED::VENT:
		m_MapInfo.m_arrVent.clear();
		break;
	case SELECTED::WALL_VERTICES:
		m_MapInfo.m_arrAllWallVertices.clear();
		m_arrCurWallVertices.clear();
		break;
	case SELECTED::TIMED_BUTTONS:
		m_MapInfo.m_arrTimedButtonsPos.clear();
		break;
	case SELECTED::DATA_UPLOAD:
		m_MapInfo.m_arrDataUploadPos.clear();
		break;
	case SELECTED::NUMBER_SEQUNECE:
		m_MapInfo.m_arrNumberSequencePos.clear();
		break;
	}
	m_bUIClicked = true;
}

void EditorScene::BacktoTitle()
{
	SceneManager::GetInstance()->RequestSceneChange(SCENE_TYPE::TITLE);
	m_bUIClicked = true;
}


