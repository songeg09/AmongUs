#include "pch.h"
#include "TitleUI.h"
#include "SceneManager.h"
#include "Button.h"

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

	m_btnStart->Init(Vector2(0.5f,0.5f), Vector2(100.0f,100.0f));

	m_arrUIElemetns.push_back(m_btnStart);
	//m_arrUIElemetns.push_back(m_btnSetting);
	//m_arrUIElemetns.push_back(m_btnExit);
}

void TitleUI::OnStartClick()
{
	SceneManager::GetInstance()->SceneChange(SCENE_TYPE::GAME);
}
