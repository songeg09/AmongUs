#pragma once
#include "UIElement.h"

class Texuture;
class TimingBar	: public UIElement
{
protected:
	Texture*				m_pTimingCursor;

	float					m_fCycleTime;
	float					m_fElapsedTime;
	float					m_fRatio = 0;

	bool					m_bPlaying;

	std::function<void()>	m_funcOnSuccessCallback;
	std::function<void()>	m_funcOnFailCallback;

	Vector2					m_vec2InitialCursorPos;
	Vector2					m_vec2CursorPos;

public:
	TimingBar();
	~TimingBar();

	void Init(
		TEXTURE_TYPE _pTimingBar,
		TEXTURE_TYPE _pTimingCursor,
		Vector2 _vec2RelativePosition,
		ANCHOR _eAnchor,
		std::function<void()> _funcOnSuccessCallback,
		std::function<void()> _funcOnFailCallback
	);
	void Update() override;
	void Render(HDC _memDC) override;

	void SetCycleTime(float _fCycleTime) { m_fCycleTime = _fCycleTime; }

	void Reset();
	void Start();
	void Stop();

	float GetRatio() { return m_fRatio; }
};

