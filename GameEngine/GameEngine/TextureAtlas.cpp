#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TextureAtlas.h"

void TextureAtlas::Load(TEXTURE_TYPE _eTextureType, Vector2 _Position, Vector2 _Size, int _Margin)
{
	m_pTexture = ResourceManager::GetInstance()->LoadTexture(_eTextureType);
	m_vec2Position = _Position;
	m_vec2Size = _Size;
}

Vector2 TextureAtlas::GetAtlasPosition()
{
	Vector2 AtlasPosition;
	AtlasPosition.m_fx = (m_vec2Position.m_fx * m_vec2Size.m_fx) + (m_vec2Position.m_fx * m_iMargin);
	AtlasPosition.m_fy = (m_vec2Position.m_fy * m_vec2Size.m_fy) + (m_vec2Position.m_fy * m_iMargin);
	return AtlasPosition;
}
