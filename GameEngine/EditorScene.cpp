#include "pch.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "InputManager.h"
#include "EditorUI.h"

EditorScene::EditorScene(std::wstring _strName)
	:Scene(_strName)
{
	m_eCurSelected = SELECTED::PLAYER_START;
	m_pBackGround = nullptr;
}

EditorScene::~EditorScene()
{
}

void EditorScene::Init()
{
	Scene::Init();

	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);

	ConfigureRenderSurface(
		Vector2(m_pBackGround->GetWidth(), m_pBackGround->GetHeight()),
		ConstValue::fGameSceneGaurdBandPx
	);

	// UI »ý¼º
	m_arrUIs.resize(static_cast<int>(UI_TYPE::END));
	EditorUI* editorUI = new EditorUI;
	editorUI->Init(
		[this]() {m_eCurSelected = SELECTED::PLAYER_START; },
		[this]() {m_eCurSelected = SELECTED::WAY_POINTS; },
		[this]() {m_eCurSelected = SELECTED::WALL_VERTICES; },
		[this]() {m_eCurSelected = SELECTED::DATA_UPLOAD; },
		[this]() {m_eCurSelected = SELECTED::TIMED_BUTTONS; },
		[this]() {m_eCurSelected = SELECTED::NUMBER_SEQUNECE; }
	);
	m_arrUIs[static_cast<int>(UI_TYPE::EDITOR)] = editorUI;
	m_UIFlags = Flag(static_cast<int>(UI_TYPE::EDITOR));

	m_eCurSelected = SELECTED::PLAYER_START;
	m_vec2CurPos = { (float)m_pBackGround->GetWidth() / 2.0f, (float)m_pBackGround->GetHeight() / 2.0f };
}

void EditorScene::Update()
{
	Move();
	Scene::Update();
}

void EditorScene::Render(HDC _memDC)
{
	Vector2 BackBufferTopLeftInScene = GetBackBufferTopLeftInScene();
	BitBlt(_memDC, 0, 0, m_vec2BackBufferSize.m_fx, m_vec2BackBufferSize.m_fy,
		m_pBackGround->GetDC(), BackBufferTopLeftInScene.m_fx, BackBufferTopLeftInScene.m_fy, SRCCOPY);
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

void EditorScene::PrintSelected(HDC _memDC)
{
	static Vector2 Pos = { m_fGuardBandPx + ConstValue::vec2BaseWindowSize.m_fx * 0.1f , m_fGuardBandPx + ConstValue::vec2BaseWindowSize.m_fy * 0.1f };

	std::wstring msg = std::format(L"FPS : {}", GetSelectedString());
	TextOutW(_memDC, Pos.m_fx, Pos.m_fy, msg.c_str(), msg.length());
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
	case SELECTED::TIMED_BUTTONS:
		return L"Timed Buttons";
	case SELECTED::DATA_UPLOAD:
		return L"Data Upload";
	case SELECTED::NUMBER_SEQUNECE:
		return L"Number Sequence";
	}
}

void EditorScene::DrawObjects()
{

}
