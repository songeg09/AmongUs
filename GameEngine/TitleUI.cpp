#include "pch.h"
#include "TitleUI.h"
#include "SceneManager.h"
#include "Button.h"
#include "ResourceManager.h";
#include "Core.h"

TitleUI::TitleUI()
{
	m_btnStart = nullptr;
	m_btnEdit = nullptr;
	m_btnQuit = nullptr;
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	m_btnStart = std::make_unique<Button>();
	m_btnEdit = std::make_unique<Button>();
	m_btnQuit = std::make_unique<Button>();

	m_btnStart->Init(TEXTURE_TYPE::BTN_START, Vector2(0.4f,0.6f), UIElement::ANCHOR::CENTER, 
		std::bind(&SceneManager::RequestSceneChange, SceneManager::GetInstance(), SCENE_TYPE::GAME)
	);
	m_btnQuit->Init(TEXTURE_TYPE::BTN_QUIT, Vector2(0.6f, 0.6f), UIElement::ANCHOR::CENTER,
		std::bind(&Core::Terminate, Core::GetInstance())
	);
	m_btnEdit->Init(TEXTURE_TYPE::BTN_EDIT, Vector2(0.5f, 0.8f), UIElement::ANCHOR::CENTER,
		std::bind(&SceneManager::RequestSceneChange, SceneManager::GetInstance(), SCENE_TYPE::EDITOR)
	);

	m_arrUIElemetns.push_back(m_btnStart.get());
	m_arrUIElemetns.push_back(m_btnEdit.get());
	m_arrUIElemetns.push_back(m_btnQuit.get());
}
