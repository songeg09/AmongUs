#include "pch.h"
#include "TitleScene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TitleUI.h"

TitleScene::TitleScene(std::wstring _strName)
	:Scene(_strName)
{
	m_pBackGround = nullptr;
}

TitleScene::~TitleScene()
{
	for (UI* ui : m_arrUIs)
		delete ui;
}

void TitleScene::Init()
{
	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::TITLE);
	ConfigureRenderSurface(
		ConstValue::vec2BaseWindowSize,
		0
	);

	m_arrUIs.resize(UI_MODE::END);
	TitleUI* titleUI = new TitleUI;
	titleUI->Init();
	m_arrUIs[UI_MODE::TITLE] = titleUI;

	m_iCurUI = UI_MODE::TITLE;

}

void TitleScene::Update()
{
	m_arrUIs[m_iCurUI]->Update();
}

void TitleScene::Render(HDC _memDC)
{
	// 1. 배경화면 그리기
	StretchBlt(_memDC, 0, 0, ConstValue::vec2BaseWindowSize.m_fx, ConstValue::vec2BaseWindowSize.m_fy,
		m_pBackGround->GetDC(), 0, 0, m_pBackGround->GetWidth(), m_pBackGround->GetHeight(), SRCCOPY);

	// 2. GUI 그리기
	m_arrUIs[m_iCurUI]->Render(_memDC);
}
