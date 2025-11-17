#pragma once
#include "ResourceManager.h"

class Texture;
class UIElement abstract
{
public:
	enum ANCHOR
	{
		TOP_LEFT,
		CENTER,
		BOTTOM_RIGHT
	};

protected:
	Texture*				m_pImage;

	Vector2					m_vec2RelativePosition;
	Vector2					m_vecAbsoluteStartPos;
	ANCHOR					m_eAnchor;

	bool					m_bVisibility;
	

public:
	UIElement();
	~UIElement();

	void Init(TEXTURE_TYPE _eTextureType, Vector2 _vec2RelativePosition, ANCHOR _eAnchor = ANCHOR::CENTER);
	virtual void Update() = 0;
	virtual void Render(HDC _memDC) = 0;

	void SetVisibility(bool _bVisibility) { m_bVisibility = _bVisibility; }

private:
	Vector2 GetAbsoluteStartPos(ANCHOR _eAnchor);
};

