#pragma once
#include "UI.h"
#include "ResourceManager.h"

class Texture;
class Button;
class TaskUI : public UI
{
protected:
	enum TASK_STATUS
	{
		PLAYING,
		FAIL,
		SUCCESS
	};

	std::function<void()>	m_funcSuccessCallback;
	std::function<void()>	m_funcFailCallback;

	TASK_STATUS				m_eTaskStatus;

	Vector2					m_vec2FrameStartPosInBackBuffer;
	Texture*				m_pFrame;
	Button*					m_btnClose;

public:
	TaskUI();
	~TaskUI();

	void Init(
		TEXTURE_TYPE            _textureTypeFrame,
		std::function<void()>	_funcOpenCallback,
		std::function<void()>	_funcCloseCallback,
		std::function<void()>	_funcSuccessCallback, 
		std::function<void()>	_funcFailCallback,
		std::function<void()>	_funcBtnCloseCallback
	);

	void Update() override;
	void Render(HDC _memDC) override;
	virtual void Reset() = 0;
	virtual void CheckWinStatus() = 0;
};

