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
		Vector2(m_pBackGround->GetWidth(), m_pBackGround->GetHeight()),
		Vector2(m_pBackGround->GetWidth(), m_pBackGround->GetHeight()),
		0
	);

	m_eCurUI = UI_MODE::TITLE;
	m_arrUIs[m_eCurUI] = new TitleUI;
	m_arrUIs[m_eCurUI]->Init();

}

void TitleScene::Update()
{
	m_arrUIs[m_eCurUI]->Update();
}

void TitleScene::Render(HDC _memDC)
{
	// 1. 배경화면 그리기
	BitBlt(_memDC, 0, 0, m_pBackGround->GetWidth(), m_pBackGround->GetHeight(),
		m_pBackGround->GetDC(), 0, 0, SRCCOPY);

	// 2. GUI 그리기
	m_arrUIs[m_eCurUI]->Render(_memDC);
}
