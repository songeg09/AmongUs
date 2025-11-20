#include "pch.h"
#include "GDIManager.h"
#include "Core.h"

GDIManager::GDIManager()
	: m_BrushList{}, m_PenList{}
{
	m_PrevBrush = nullptr;
	m_PrevPen = nullptr;

	CreateMyPen();
	CreateMyBrush();

	m_TransparencyBlendFunc = {};
	m_TransparencyBlendFunc.BlendOp = AC_SRC_OVER;      // 고정
	m_TransparencyBlendFunc.BlendFlags = 0;             // 고정
	m_TransparencyBlendFunc.SourceConstantAlpha = 100;  // 전체 반투명도(0~255)
	m_TransparencyBlendFunc.AlphaFormat = 0;

	m_GreenBlendFunc = {};

	// 버튼 효과 추가용 DC 설정
	m_TempBmp = CreateCompatibleBitmap(Core::GetInstance()->GetMainDC(), 200, 200);				// 버튼 사이즈는 임시로 200x200을 넘지 않는다고 가정
	m_BtnConfigureDC = CreateCompatibleDC(Core::GetInstance()->GetMainDC());

	HBITMAP hOldBitMap = (HBITMAP)SelectObject(m_BtnConfigureDC, m_TempBmp);
	DeleteObject(hOldBitMap);
}
GDIManager::~GDIManager()
{
	ReleaseMyPen();
	ReleaseMyBrush();
}

void GDIManager::Init()
{
	

}

void GDIManager::CreateMyPen()
{
	m_PenList[static_cast<int>(PEN_TYPE::BLACK)] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	m_PenList[static_cast<int>(PEN_TYPE::WHITE)] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	m_PenList[static_cast<int>(PEN_TYPE::RED)] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_PenList[static_cast<int>(PEN_TYPE::GREEN)] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_PenList[static_cast<int>(PEN_TYPE::BLUE)] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

void GDIManager::ReleaseMyPen()
{
	for (int i = 0; i < static_cast<int>(PEN_TYPE::END); ++i)
	{
		if (m_PenList[i] == nullptr)
			continue;
		DeleteObject(m_PenList[i]);
	}
}

void GDIManager::CreateMyBrush()
{
	m_BrushList[static_cast<int>(BRUSH_TYPE::HOLLOW)] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_BrushList[static_cast<int>(BRUSH_TYPE::BLACK)] = CreateSolidBrush(RGB(0, 0, 0));
	m_BrushList[static_cast<int>(BRUSH_TYPE::WHITE)] = CreateSolidBrush(RGB(255, 255, 255));
	m_BrushList[static_cast<int>(BRUSH_TYPE::RED)] = CreateSolidBrush(RGB(255, 0, 0));
	m_BrushList[static_cast<int>(BRUSH_TYPE::GREEN)] = CreateSolidBrush(RGB(0, 255, 0));
	m_BrushList[static_cast<int>(BRUSH_TYPE::BLUE)] = CreateSolidBrush(RGB(0, 0, 255));
}

void GDIManager::ReleaseMyBrush()
{
	for (int i = 0; i < static_cast<int>(BRUSH_TYPE::END); ++i)
	{
		if (i == static_cast<int>(BRUSH_TYPE::HOLLOW) || m_BrushList[i] == nullptr)
			continue;
		DeleteObject(m_PenList[i]);
	}
}