#pragma once
class TextureAtlas
{
private:
	Texture* m_pTexture;
	Vector2 m_vec2Position;
	Vector2 m_vec2Size;
	int m_iMargin;

public:
	void Load(TEXTURE_TYPE _eTextureType, Vector2 _Position, Vector2 _Size, int _Margin);

	HDC GetDC() { return m_pTexture->GetDC(); }
	int GetWidht() { return m_vec2Size.m_fx; }
	int GetHeight() { return m_vec2Size.m_fy; }
	Vector2 GetSize() { return m_vec2Size; }
	Vector2 GetAtlasPosition();
};

