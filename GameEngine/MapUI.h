#pragma once
#include "UI.h"

class Texture;
class Player;
class Button;
class MinimapProvider;
class MapUI : public UI
{
private:
	std::weak_ptr<MinimapProvider>		m_minimapProvider;
	std::shared_ptr<Button>				m_btnClose;

	std::weak_ptr<Texture>				m_pMap;
	std::weak_ptr<Texture>				m_pPlayerIcon;
	std::weak_ptr<Texture>				m_pObjectIcon;

	Vector2								m_vec2MapStartPosInBackBuffer;
	Vector2								m_vec2Ratio;
	
public:
	MapUI();
	~MapUI();

	void Init(std::shared_ptr<MinimapProvider> _minimapProvider, std::function<void()> _CloseBtnCallback);
	void Render(HDC _memDC) override;
};

