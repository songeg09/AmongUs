#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "PathManager.h"
#include "GDIManager.h"
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

	SceneManager::GetInstance()->ProcessSceneChange();
}

void Core::Render()
{
	if (SceneManager::GetInstance()->GetCurScene() == nullptr)
		return;
	SceneManager::GetInstance()->Render(m_hBackDC);

	Vector2 ViewPortTopLeft = SceneManager::GetInstance()->GetCurScene()->GetViewportTopLeftInBackBuffer();

	std::wstring FPSMessage = std::format(L"FPS : {}", TimerManager::GetInstance()->intGetFPS());
	TextOutW(m_hBackDC, ViewPortTopLeft.m_fx, ViewPortTopLeft.m_fy, FPSMessage.c_str(), FPSMessage.length());
	
	//Vector2 vec2Resoultion = SettingsManager::GetInstance()->GetInstance()->GetResolution();
	BitBlt(m_hDC, 0, 0, ConstValue::vec2BaseWindowSize.m_fx, ConstValue::vec2BaseWindowSize.m_fy,
		m_hBackDC, ViewPortTopLeft.m_fx, ViewPortTopLeft.m_fy, SRCCOPY);
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
		Vector2 BackBufferSize = SceneManager::GetInstance()->GetCurScene()->GetBackBufferSize();
		m_hBackBitMap = CreateCompatibleBitmap(m_hDC, BackBufferSize.m_fx, BackBufferSize.m_fy);
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

void Core::Terminate()
{
	SendMessage(m_hWnd, WM_DESTROY, 0, 0);
}



