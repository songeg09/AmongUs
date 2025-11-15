#include "pch.h"
#include "TitleUI.h"
#include "SceneManager.h"
#include "Button.h"
#include "ResourceManager.h";

TitleUI::TitleUI()
{
	m_btnStart = nullptr;
	m_btnSetting = nullptr;
	m_btnExit = nullptr;
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	m_btnStart = new Button;
	//m_btnSetting = new Button;
	//m_btnExit = new Button;

	m_btnStart->Init(TEXTURE_TYPE::BTN_START, Vector2(0.5f,0.6f), UIElement::ANCHOR::CENTER, std::bind(&TitleUI::OnClick, this));

	m_arrUIElemetns.push_back(m_btnStart);
	//m_arrUIElemetns.push_back(m_btnSetting);
	//m_arrUIElemetns.push_back(m_btnExit);
}

void TitleUI::OnClick()
{
	SceneManager::GetInstance()->SceneChange(SCENE_TYPE::GAME);
}
