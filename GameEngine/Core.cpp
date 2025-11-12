#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "PathManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "SettingsManager.h"

Core::Core()
{
	m_hBackBitMap = nullptr;
	m_hBackDC = nullptr;
	m_hDC = nullptr;
	m_hWnd = nullptr;
}
Core::~Core()
{
	if (m_hBackBitMap != nullptr)
		DeleteObject(m_hBackBitMap);
	if (m_hBackDC != nullptr)
		DeleteDC(m_hBackDC);
	if (m_hWnd != nullptr && m_hDC != nullptr)
		ReleaseDC(m_hWnd, m_hDC);
}

void Core::Update()
{
	TimerManager::GetInstance()->Update();
	InputManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();
}

void Core::Render()
{
	if (SceneManager::GetInstance()->GetCurScene() == nullptr)
		return;
	SceneManager::GetInstance()->Render(m_hBackDC);

	Vector2 ViewPortTopLeft = SceneManager::GetInstance()->GetCurScene()->GetViewportTopLeftInBackBuffer();
	Vector2 ViewPortSize = SceneManager::GetInstance()->GetCurScene()->GetViewPortSize();

	std::wstring FPSMessage = std::format(L"FPS : {}", TimerManager::GetInstance()->intGetFPS());
	TextOutW(m_hBackDC, ViewPortTopLeft.m_fx, ViewPortTopLeft.m_fy, FPSMessage.c_str(), FPSMessage.length());
	
	Vector2 vec2Resoultion = SettingsManager::GetInstance()->GetInstance()->GetResolution();
	StretchBlt(m_hDC, 0, 0, vec2Resoultion.m_fx, vec2Resoultion.m_fy,
		m_hBackDC, ViewPortTopLeft.m_fx, ViewPortTopLeft.m_fy, ViewPortSize.m_fx, ViewPortSize.m_fy, SRCCOPY);
}


void Core::Init(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hDC = GetDC(m_hWnd);

	TimerManager::GetInstance()->Init();

	InputManager::GetInstance()->Init();

	PathManager::GetInstance()->Init();

	ResourceManager::GetInstance()->Init();

	CollisionManager::GetInstance()->Init();

	SceneManager::GetInstance()->Init();

	SettingsManager::GetInstance()->Init();

	CreateBackDC();
}

void Core::CreateBackDC()
{
	if (m_hBackBitMap != nullptr)
		DeleteObject(m_hBackBitMap);
	if (m_hBackDC != nullptr)
		DeleteDC(m_hBackDC);
	if (SceneManager::GetInstance()->GetCurScene() != nullptr)
	{
		// 실제 출력에 필요한 두배 크기의 백버퍼 크기 생성
		Vector2 ViewPortSize = SceneManager::GetInstance()->GetCurScene()->GetViewPortSize();
		m_hBackBitMap = CreateCompatibleBitmap(m_hDC, ViewPortSize.m_fx * 2, ViewPortSize.m_fy * 2);
		m_hBackDC = CreateCompatibleDC(m_hDC);
		HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitMap);
		DeleteObject(hOldBitMap);
	}
}

void Core::GameLoop()
{
	Update();
	Render();
}

