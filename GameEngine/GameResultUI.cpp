#include "pch.h"
#include "GameResultUI.h"
#include "GameMode.h"
#include "Texture.h"
#include "Button.h"
#include "ResourceManager.h"
#include "SceneManager.h"

GameResultUI::GameResultUI()
{
}

GameResultUI::~GameResultUI()
{
}

void GameResultUI::Init(std::shared_ptr<GameMode> _GameMode, std::function<void()> _funcPlayAgainCallback, std::function<void()> _funcQuitCallback)
{
	UI::Init();
	m_GameMode = _GameMode;

	m_btnPlayAgain = std::make_shared<Button>();
	m_btnPlayAgain->Init(TEXTURE_TYPE::BTN_PLAYAGAIN,Vector2(0.4,0.7),UIElement::ANCHOR::CENTER, _funcPlayAgainCallback);
	m_arrUIElemetns.push_back(m_btnPlayAgain);

	m_btnQuit = std::make_shared<Button>();
	m_btnQuit->Init(TEXTURE_TYPE::BTN_QUIT, Vector2(0.6, 0.7), UIElement::ANCHOR::CENTER, _funcQuitCallback);
	m_arrUIElemetns.push_back(m_btnQuit);
	
}

void GameResultUI::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	TransparentBlt(
		_memDC,
		m_vec2ResultTextureStartPos.m_fx, m_vec2ResultTextureStartPos.m_fy,
		m_pCurResult.lock()->GetWidth(), m_pCurResult.lock()->GetHeight(),
		m_pCurResult.lock()->GetDC(),
		0,0,
		m_pCurResult.lock()->GetWidth(), m_pCurResult.lock()->GetHeight(),
		RGB(255,0,255)
	);

	UI::Render(_memDC);
}

void GameResultUI::Open()
{
	if (m_GameMode.lock()->GetGameState() == GameMode::GAME_STATE::LOSE)
		m_pCurResult = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::LOSE);
	else
		m_pCurResult = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::WIN);

	UpdateResultStartPos();

	UI::Open();
}

void GameResultUI::UpdateResultStartPos()
{
	m_vec2ResultTextureStartPos = SceneManager::GetInstance()->GetCurScene()->GetBackBufferSize();
	m_vec2ResultTextureStartPos.m_fx /= 2;
	m_vec2ResultTextureStartPos.m_fy /= 2;
	m_vec2ResultTextureStartPos.m_fx -= m_pCurResult.lock()->GetWidth() / 2;
	m_vec2ResultTextureStartPos.m_fy -= m_pCurResult.lock()->GetHeight();
	m_vec2ResultTextureStartPos.m_fy += 10.0f;
}

