#pragma once
#include "UI.h"

class Texture;
class Player;
class Button;
class MinimapProvider;
class MapUI : public UI
{
private:
	MinimapProvider*	m_minimapProvider;
	Button*				m_btnClose;

	Texture*			m_pMap;
	Texture*			m_pPlayerIcon;
	Texture*			m_pObjectIcon;

	Vector2				m_vec2MapStartPosInBackBuffer;
	Vector2				m_vec2Ratio;
	
public:
	MapUI();
	~MapUI();

	void Init(MinimapProvider* _minimapProvider, std::function<void()> _CloseBtnCallback);
	void Render(HDC _memDC) override;
};

