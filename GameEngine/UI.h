#pragma once

class UIElement;
class UI abstract
{
protected:
	bool									m_bVisibility;
	std::vector<UIElement*>					m_arrUIElemetns;

	std::function<void()>					m_funcOpenCallback;
	std::function<void()>					m_funcCloseCallback;

public:
	UI();
	virtual ~UI();

	void Init(std::function<void()>	_funcOpenCallback = nullptr ,std::function<void()> _funcCloseCallback = nullptr);
	virtual void Update();
	virtual void Render(HDC _memDC);
	void SetVisibility(bool _bVisibility) { m_bVisibility = _bVisibility; }

	virtual void Open();
	virtual void Close();
};

