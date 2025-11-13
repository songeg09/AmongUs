#include "pch.h"
#include "MapUI.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"

MapUI::MapUI()
{
	m_pMap = nullptr;
}

MapUI::~MapUI()
{
}

void MapUI::Init()
{
	m_pMap = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::MAP);
}

void MapUI::Render(HDC _memDC)
{
	Vector2 MapStartPos = SceneManager::GetInstance()->GetCurScene()->GetBackBufferSize();
	MapStartPos.m_fx /= 2;
	MapStartPos.m_fy /= 2;
	MapStartPos.m_fx -= m_pMap->GetWidth() / 2;
	MapStartPos.m_fy -= m_pMap->GetHeight() / 2;

	TransparentBlt(_memDC, MapStartPos.m_fx, MapStartPos.m_fy,
		m_pMap->GetWidth(), m_pMap->GetHeight(),
		m_pMap->GetDC(),
		0,0,
		m_pMap->GetWidth(), m_pMap->GetHeight(),
		RGB(255,0,255)
	);

	UI::Render(_memDC);
}
