#include "pch.h"
#include "MenuUI.h"
#include "TimerManager.h"
#include "Button.h"

MenuUI::MenuUI()
{
	m_btnPlayAgain = nullptr;
	m_btnQuit = nullptr;
}

MenuUI::~MenuUI()
{
}

void MenuUI::Init(std::function<void()> _funcPlayAgainCallback, std::function<void()> _funcQuitCallback)
{
	m_btnPlayAgain = new Button;
	m_btnPlayAgain->Init(TEXTURE_TYPE::BTN_PLAYAGAIN, Vector2(0.4,0.5),UIElement::ANCHOR::CENTER, _funcPlayAgainCallback);
	m_arrUIElemetns.push_back(m_btnPlayAgain);

	m_btnQuit = new Button;
	m_btnQuit->Init(TEXTURE_TYPE::BTN_QUIT, Vector2(0.6, 0.5), UIElement::ANCHOR::CENTER, _funcQuitCallback);
	m_arrUIElemetns.push_back(m_btnQuit);
}


void MenuUI::Open()
{
	TimerManager::GetInstance()->Pause();
	UI::Open();
}

void MenuUI::Close()
{
	TimerManager::GetInstance()->Resume();
	UI::Close();
}
