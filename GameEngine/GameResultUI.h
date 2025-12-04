#pragma once
#include "UI.h"

class GameMode;
class Button;
class Texture;
class GameResultUI : public UI
{
private:
	std::weak_ptr<GameMode>					m_GameMode;
	std::weak_ptr<Texture>					m_pCurResult;

	std::shared_ptr<Button>					m_btnPlayAgain;
	std::shared_ptr<Button>					m_btnQuit;

	Vector2									m_vec2ResultTextureStartPos;

public:
	GameResultUI();
	~GameResultUI();

	void Init(std::shared_ptr<GameMode> _GameMode, std::function<void()> _funcPlayAgainCallback, std::function<void()> _funcQuitCallback);
	void Render(HDC _memDC) override;
	void Open() override;
	void UpdateResultStartPos();
};

