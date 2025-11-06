#include "pch.h"
#include "GameResource.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TextureAtlas.h"

void TextureAtlas::Load(TEXTURE_TYPE _eTextureType, Vector2 _Position, Vector2 _Size, int _Margin, bool _Flip)
{
	if (_Flip == false)
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(_eTextureType);
	else
		m_pTexture = ResourceManager::GetInstance()->LoadTexture(_eTextureType, true);
	m_vec2Position = _Position;
	m_vec2Size = _Size;
	m_iMargin = _Margin;
	m_bFlip = _Flip;
}

Vector2 TextureAtlas::GetAtlasPosition()
{
	Vector2 AtlasPosition;

	if (m_bFlip == false)
	{
		AtlasPosition.m_fx = (m_vec2Position.m_fx * m_vec2Size.m_fx) + (m_vec2Position.m_fx * m_iMargin);
		AtlasPosition.m_fy = (m_vec2Position.m_fy * m_vec2Size.m_fy) + (m_vec2Position.m_fy * m_iMargin);
	}
	else
	{
		AtlasPosition.m_fx = (m_pTexture->GetWidth() - 1) - ((m_vec2Position.m_fx + 1) * (m_vec2Size.m_fx)) + (m_vec2Position.m_fx * m_iMargin);
		AtlasPosition.m_fy = (m_vec2Position.m_fy * m_vec2Size.m_fy) + (m_vec2Position.m_fy * m_iMargin);
	}

	return AtlasPosition;
}
