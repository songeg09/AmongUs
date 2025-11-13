#pragma once
#include "UI.h"

class Texture;
class TextureAtlas;
class GameScene;
class Character;
class MapUI : public UI
{
private:
	Texture*		m_pMap;
	TextureAtlas*	m_pPlayerIcon;

	Vector2			m_vec2MapStartPosInBackBuffer;
	Vector2			m_vec2Ratio;

	GameScene*		m_sceneCurGameScene;
	Character*		m_Player;
	
public:
	MapUI();
	~MapUI();

	void Init() override;
	void Render(HDC _memDC) override;
};

