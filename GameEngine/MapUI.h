#pragma once
#include "UI.h"

class Texture;
class Player;
class Button;
class MapUI : public UI
{
private:
	Button*			m_ExitButton;

	Texture*		m_pMap;
	Texture*		m_pPlayerIcon;

	Vector2			m_vec2MapStartPosInBackBuffer;
	Vector2			m_vec2Ratio;

	const Player*	m_Player;
	
public:
	MapUI();
	~MapUI();

	void Init(Player* _Player, std::function<void()> _btnExitCallback);
	void Render(HDC _memDC) override;
};

