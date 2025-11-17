#include "pch.h"
#include "MapUI.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "GameScene.h"
#include "Player.h"
#include "Button.h"

MapUI::MapUI()
{
	m_pMap = nullptr;
}

MapUI::~MapUI()
{
}

void MapUI::Init(Player* _Player, std::function<void()> _btnExitCallback)
{
	m_Player = _Player;

	m_pMap = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::MAP);
	m_pPlayerIcon = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::CHARACTER_ICON);
	
	Texture* RealMap = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::SINGLEPLAYMAP);

	m_vec2MapStartPosInBackBuffer = SceneManager::GetInstance()->GetCurScene()->GetBackBufferSize();
	m_vec2MapStartPosInBackBuffer.m_fx /= 2;
	m_vec2MapStartPosInBackBuffer.m_fy /= 2;
	m_vec2MapStartPosInBackBuffer.m_fx -= m_pMap->GetWidth() / 2;
	m_vec2MapStartPosInBackBuffer.m_fy -= m_pMap->GetHeight() / 2;

	m_vec2Ratio = Vector2((float)m_pMap->GetWidth() / (float)RealMap->GetWidth(), (float)m_pMap->GetHeight() / (float)RealMap->GetHeight());

	m_ExitButton = new Button;
	m_ExitButton->Init(TEXTURE_TYPE::BTN_X, Vector2(0.85, 0.15), UIElement::ANCHOR::CENTER, _btnExitCallback);
	m_arrUIElemetns.push_back(m_ExitButton);
}

void MapUI::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	TransparentBlt(_memDC, m_vec2MapStartPosInBackBuffer.m_fx, m_vec2MapStartPosInBackBuffer.m_fy,
		m_pMap->GetWidth(), m_pMap->GetHeight(),
		m_pMap->GetDC(),
		0,0,
		m_pMap->GetWidth(), m_pMap->GetHeight(),
		RGB(255,0,255)
	);

	Vector2 PlayerPosOnMap = m_Player->GetPosition();
	PlayerPosOnMap.m_fx = PlayerPosOnMap.m_fx * m_vec2Ratio.m_fx;
	PlayerPosOnMap.m_fy = PlayerPosOnMap.m_fy * m_vec2Ratio.m_fy;

	TransparentBlt(_memDC, 
		m_vec2MapStartPosInBackBuffer.m_fx + PlayerPosOnMap.m_fx - m_pPlayerIcon->GetWidth() / 2, 
		m_vec2MapStartPosInBackBuffer.m_fy + PlayerPosOnMap.m_fy - m_pPlayerIcon->GetHeight() / 2,
		m_pPlayerIcon->GetWidth(), m_pPlayerIcon->GetHeight(),
		m_pPlayerIcon->GetDC(),
		0, 0,
		m_pPlayerIcon->GetWidth(), m_pPlayerIcon->GetHeight(),
		RGB(255, 0, 255)
	);

	UI::Render(_memDC);
}
