#include "pch.h"
#include "UI.h"
#include "UIElement.h"

UI::UI()
{
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
	for (UIElement* element : m_arrUIElemetns)
	{
		element->Update();
	}
}

void UI::Render(HDC _memDC)
{
	for (UIElement* element : m_arrUIElemetns)
	{
		element->Render(_memDC);
	}
}
