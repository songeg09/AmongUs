#include "pch.h"
#include "TitleScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TitleUI.h"

TitleScene::TitleScene(std::wstring _strName)
	:Scene(_strName)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Scene::Init();

	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::TITLE);
	ConfigureRenderSurface(
		ConstValue::vec2BaseWindowSize,
		0
	);

	m_arrUIs.resize(static_cast<int>(UI_TYPE::END));
	std::unique_ptr<TitleUI> titleUI = std::make_unique<TitleUI>();
	titleUI->Init();
	m_arrUIs[static_cast<int>(UI_TYPE::TITLE)] = std::move(titleUI);
	m_UIFlags = Flag(static_cast<int>(UI_TYPE::TITLE));
}

void TitleScene::Update()
{
	Scene::Update();
}

void TitleScene::Render(HDC _memDC)
{
	// 1. 배경화면 그리기
	StretchBlt(_memDC, 0, 0, ConstValue::vec2BaseWindowSize.m_fx, ConstValue::vec2BaseWindowSize.m_fy,
		m_pBackGround.lock()->GetDC(), 0, 0, m_pBackGround.lock()->GetWidth(), m_pBackGround.lock()->GetHeight(), SRCCOPY);

	// 2. GUI 그리기
	Scene::Render(_memDC);
}
