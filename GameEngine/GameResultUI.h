#pragma once
#include "UI.h"

class GameMode;
class Button;
class Texture;
class GameResultUI : public UI
{
private:
	GameMode*				m_GameMode;

	Texture*				m_pCurResult;

	Button*					m_btnPlayAgain;
	Button*					m_btnQuit;

	Vector2					m_vec2ResultTextureStartPos;


public:
	GameResultUI();
	~GameResultUI();

	void Init(GameMode* _GameMode, std::function<void()> _funcPlayAgainCallback, std::function<void()> _funcQuitCallback);
	void Render(HDC _memDC) override;
	void Open() override;
	void UpdateResultStartPos();
};

