#include "pch.h"
#include "PlayerStatusUI.h"
#include "Button.h"
#include "ProgressBar.h"
#include "GameMode.h"
#include "Player.h "
#include "SceneManager.h"

PlayerStatusUI::PlayerStatusUI()
{
	m_btnUse = nullptr;
	m_btnMap = nullptr;
	m_btnSetting = nullptr;
	m_GameMode = nullptr;
}

PlayerStatusUI::~PlayerStatusUI()
{
}

void PlayerStatusUI::Init(GameMode* _GameMode, Player* _Player, std::function<void()> _mapBtnCallback)
{
	UI::Init();

	m_GameMode = _GameMode;
	m_Player = _Player;

	m_btnUse = new Button;
	m_btnUse->Init(TEXTURE_TYPE::BTN_USE, Vector2(0.95, 0.9), UIElement::ANCHOR::CENTER, std::bind(&Player::UseInteractableObject, m_Player));
	m_arrUIElemetns.push_back(m_btnUse);

	m_btnMap = new Button;
	m_btnMap->Init(TEXTURE_TYPE::BTN_MAP, Vector2(0.95, 0.07), UIElement::ANCHOR::CENTER, _mapBtnCallback);
	m_arrUIElemetns.push_back(m_btnMap);

	m_btnSetting = new Button;
	m_btnSetting->Init(TEXTURE_TYPE::BTN_SETTING, Vector2(0.95, 0.17), UIElement::ANCHOR::CENTER);
	m_arrUIElemetns.push_back(m_btnSetting);

	m_progressbarTasks = new ProgressBar;
	m_progressbarTasks->Init(TEXTURE_TYPE::PROGRESSBAR_FRAME, TEXTURE_TYPE::PROGRESSBAR, Vector2(0.01, 0.01), UIElement::ANCHOR::TOP_LEFT);
	m_arrUIElemetns.push_back(m_progressbarTasks);
}


void PlayerStatusUI::Update()
{
	if (m_bVisibility == false)
		return;

	if (m_Player != nullptr)
	{
		if (m_Player->GetInteractableObject() != nullptr)
			m_btnUse->SetActivate(true);
		else
			m_btnUse->SetActivate(false);
	}

	UI::Update();

	m_progressbarTasks->SetProgress(m_GameMode->GetProgress());
}

void PlayerStatusUI::Render(HDC _memDC)
{
	UI::Render(_memDC);

	static std::wstring txt = L"TOTAL TASK COMPLETED";
	TextOutW(_memDC, 500, 500, txt.c_str(), txt.length());
}
