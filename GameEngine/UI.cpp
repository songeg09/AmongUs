#include "pch.h"
#include "UI.h"
#include "UIElement.h"

UI::UI()
{
	m_bVisibility = false;
}

UI::~UI()
{
	for (UIElement* element : m_arrUIElemetns)
	{
		delete element;
	}
	m_arrUIElemetns.clear();
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
