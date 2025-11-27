#include "pch.h"
#include "UI.h"
#include "UIElement.h"
#include "MenuUI.h"

UI::UI()
{
	m_bVisibility = false;
	m_funcOpenCallback = nullptr;
	m_funcCloseCallback = nullptr;
}

UI::~UI()
{
	for (UIElement* element : m_arrUIElemetns)
	{
		delete element;
	}
	m_arrUIElemetns.clear();
}


void UI::Init(std::function<void()> _funcOpenCallback, std::function<void()> _funcCloseCallback)
{
	m_funcOpenCallback = _funcOpenCallback;
	m_funcCloseCallback = _funcCloseCallback;
}

void UI::Update()
{
	if (m_bVisibility == false)
		return;

	for (UIElement* element : m_arrUIElemetns)
	{
		element->Update();
	}
}

void UI::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	for (UIElement* element : m_arrUIElemetns)
	{
		element->Render(_memDC);
	}
}

void UI::Open()
{
	SetVisibility(true);
	if (m_funcOpenCallback != nullptr)
		m_funcOpenCallback();
}

void UI::Close()
{
	SetVisibility(false);
	if (m_funcCloseCallback != nullptr)
		m_funcCloseCallback();
}


