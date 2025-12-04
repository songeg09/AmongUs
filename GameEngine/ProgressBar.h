#pragma once
#include "UIElement.h"

class Texture;
class ProgressBar : public UIElement
{
private:
	std::weak_ptr<Texture>	m_pProgressBar;
	Vector2					m_vec2ProgressStartPos;
	float					m_fProgress;

public:
	ProgressBar();
	~ProgressBar();

	void Init(TEXTURE_TYPE _eFrame, TEXTURE_TYPE _eProgress, Vector2 _vec2RelativePosition, ANCHOR _eAnchor = ANCHOR::CENTER);
	void Update() override;
	void Render(HDC _memDC) override;

	void SetProgress(float _fProgress) { m_fProgress = _fProgress; }
};

