#pragma once
class TextureAtlas : public GameResource
{
private:
	Texture*		m_pTexture;
	Vector2			m_vec2Position;
	Vector2			m_vec2Size;
	int				m_iMargin;
	bool			m_bFlip;

public:
	void Load(TEXTURE_TYPE _eTextureType, Vector2 _Position, Vector2 _Size, int _Margin, bool _Flip);

	HDC GetDC() { return m_pTexture->GetDC(); }
	int GetWidth() { return m_vec2Size.m_fx; }
	int GetHeight() { return m_vec2Size.m_fy; }
	Vector2 GetSize() { return m_vec2Size; }
	Vector2 GetAtlasPosition();
	bool GetFlip() { return m_bFlip; }
};

