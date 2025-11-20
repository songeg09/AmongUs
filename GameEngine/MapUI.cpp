#include "pch.h"
#include "MapUI.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "GameScene.h"
#include "Player.h"
#include "Button.h"
#include "GameObject.h"

MapUI::MapUI()
{
	m_pMap = nullptr;
}

MapUI::~MapUI()
{
}

void MapUI::Init(MinimapProvider* _minimapProvider, std::function<void()> _CloseBtnCallback)
{
	UI::Init();

	m_minimapProvider = _minimapProvider;

	m_pMap = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::MAP);
	m_pPlayerIcon = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::CHARACTER_ICON);
	m_pObjectIcon = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::OBJECT_ICON);

	Texture* RealMap = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);

	m_vec2MapStartPosInBackBuffer = SceneManager::GetInstance()->GetCurScene()->GetBackBufferSize();
	m_vec2MapStartPosInBackBuffer.m_fx /= 2;
	m_vec2MapStartPosInBackBuffer.m_fy /= 2;
	m_vec2MapStartPosInBackBuffer.m_fx -= m_pMap->GetWidth() / 2;
	m_vec2MapStartPosInBackBuffer.m_fy -= m_pMap->GetHeight() / 2;

	m_vec2Ratio = Vector2((float)m_pMap->GetWidth() / (float)RealMap->GetWidth(), (float)m_pMap->GetHeight() / (float)RealMap->GetHeight());

	m_btnClose = new Button;
	m_btnClose->Init(TEXTURE_TYPE::BTN_X, Vector2(0.15, 0.15), UIElement::ANCHOR::CENTER, _CloseBtnCallback);
	m_arrUIElemetns.push_back(m_btnClose);
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

	static Vector2 PlayerPos;
	static Vector2 ObjectPos;

	PlayerPos = m_minimapProvider->GetPlayerPos();
	PlayerPos.m_fx = PlayerPos.m_fx * m_vec2Ratio.m_fx;
	PlayerPos.m_fy = PlayerPos.m_fy * m_vec2Ratio.m_fy;

	TransparentBlt(_memDC, 
		m_vec2MapStartPosInBackBuffer.m_fx + PlayerPos.m_fx - m_pPlayerIcon->GetWidth() / 2,
		m_vec2MapStartPosInBackBuffer.m_fy + PlayerPos.m_fy - m_pPlayerIcon->GetHeight() / 2,
		m_pPlayerIcon->GetWidth(), m_pPlayerIcon->GetHeight(),
		m_pPlayerIcon->GetDC(),
		0, 0,
		m_pPlayerIcon->GetWidth(), m_pPlayerIcon->GetHeight(),
		RGB(255, 0, 255)
	);

	

	for (GameObject* obejct : m_minimapProvider->GetGameObjects())
	{
		ObjectPos = obejct->GetPosition();
		ObjectPos.m_fx = ObjectPos.m_fx * m_vec2Ratio.m_fx;
		ObjectPos.m_fy = ObjectPos.m_fy * m_vec2Ratio.m_fy;

		TransparentBlt(_memDC,
			m_vec2MapStartPosInBackBuffer.m_fx + ObjectPos.m_fx - m_pObjectIcon->GetWidth() / 2,
			m_vec2MapStartPosInBackBuffer.m_fy + ObjectPos.m_fy - m_pObjectIcon->GetHeight() / 2,
			m_pObjectIcon->GetWidth(), m_pObjectIcon->GetHeight(),
			m_pObjectIcon->GetDC(),
			0, 0,
			m_pObjectIcon->GetWidth(), m_pObjectIcon->GetHeight(),
			RGB(255, 0, 255)
		);
	}

	UI::Render(_memDC);
}
