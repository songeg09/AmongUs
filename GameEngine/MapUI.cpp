#include "pch.h"
#include "MapUI.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TextureAtlas.h"
#include "GameScene.h"
#include "Player.h"
#include "Button.h"
#include "Interactable.h"

MapUI::MapUI()
{
}

MapUI::~MapUI()
{
}

void MapUI::Init(std::shared_ptr<MinimapProvider> _minimapProvider, std::function<void()> _CloseBtnCallback)
{
	UI::Init();

	m_minimapProvider = _minimapProvider;

	m_pMap = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::MAP);
	m_pPlayerIcon = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::CHARACTER_ICON);
	m_pObjectIcon = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::OBJECT_ICON);

	Texture* RealMap = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND).get();

	m_vec2MapStartPosInBackBuffer = SceneManager::GetInstance()->GetCurScene()->GetBackBufferSize();
	m_vec2MapStartPosInBackBuffer.m_fx /= 2;
	m_vec2MapStartPosInBackBuffer.m_fy /= 2;
	m_vec2MapStartPosInBackBuffer.m_fx -= m_pMap.lock()->GetWidth() / 2;
	m_vec2MapStartPosInBackBuffer.m_fy -= m_pMap.lock()->GetHeight() / 2;

	m_vec2Ratio = Vector2((float)m_pMap.lock()->GetWidth() / (float)RealMap->GetWidth(), (float)m_pMap.lock()->GetHeight() / (float)RealMap->GetHeight());

	m_btnClose = std::make_shared<Button>();
	m_btnClose->Init(TEXTURE_TYPE::BTN_X, Vector2(0.15, 0.15), UIElement::ANCHOR::CENTER, _CloseBtnCallback);
	m_arrUIElemetns.push_back(m_btnClose);
}

void MapUI::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	TransparentBlt(_memDC, m_vec2MapStartPosInBackBuffer.m_fx, m_vec2MapStartPosInBackBuffer.m_fy,
		m_pMap.lock()->GetWidth(), m_pMap.lock()->GetHeight(),
		m_pMap.lock()->GetDC(),
		0,0,
		m_pMap.lock()->GetWidth(), m_pMap.lock()->GetHeight(),
		RGB(255,0,255)
	);

	static Vector2 PlayerPos;
	static Vector2 ObjectPos;

	PlayerPos = m_minimapProvider.lock()->GetPlayerPos();
	PlayerPos.m_fx = PlayerPos.m_fx * m_vec2Ratio.m_fx;
	PlayerPos.m_fy = PlayerPos.m_fy * m_vec2Ratio.m_fy;

	TransparentBlt(_memDC, 
		m_vec2MapStartPosInBackBuffer.m_fx + PlayerPos.m_fx - m_pPlayerIcon.lock()->GetWidth() / 2,
		m_vec2MapStartPosInBackBuffer.m_fy + PlayerPos.m_fy - m_pPlayerIcon.lock()->GetHeight() / 2,
		m_pPlayerIcon.lock()->GetWidth(), m_pPlayerIcon.lock()->GetHeight(),
		m_pPlayerIcon.lock()->GetDC(),
		0, 0,
		m_pPlayerIcon.lock()->GetWidth(), m_pPlayerIcon.lock()->GetHeight(),
		RGB(255, 0, 255)
	);

	

	for (Interactable* obejct : m_minimapProvider.lock()->GetGameObjects())
	{
		ObjectPos = obejct->GetPosition();
		ObjectPos.m_fx = ObjectPos.m_fx * m_vec2Ratio.m_fx;
		ObjectPos.m_fy = ObjectPos.m_fy * m_vec2Ratio.m_fy;

		TransparentBlt(_memDC,
			m_vec2MapStartPosInBackBuffer.m_fx + ObjectPos.m_fx - m_pObjectIcon.lock()->GetWidth() / 2,
			m_vec2MapStartPosInBackBuffer.m_fy + ObjectPos.m_fy - m_pObjectIcon.lock()->GetHeight() / 2,
			m_pObjectIcon.lock()->GetWidth(), m_pObjectIcon.lock()->GetHeight(),
			m_pObjectIcon.lock()->GetDC(),
			0, 0,
			m_pObjectIcon.lock()->GetWidth(), m_pObjectIcon.lock()->GetHeight(),
			RGB(255, 0, 255)
		);
	}

	UI::Render(_memDC);
}
