#include "pch.h"
#include "SettingsManager.h"
#include "InputManager.h"
#include "Core.h"

SettingsManager::SettingsManager()
{

}

SettingsManager::~SettingsManager()
{

}

void SettingsManager::Init()
{
	SetResoultion();
	InputManager::GetInstance()->RegistKey(VK_LBUTTON);
	InputManager::GetInstance()->RegistKey(VK_ESCAPE);
	InputManager::GetInstance()->RegistKey('W');
	InputManager::GetInstance()->RegistKey('A');
	InputManager::GetInstance()->RegistKey('S');
	InputManager::GetInstance()->RegistKey('D');
	InputManager::GetInstance()->RegistKey(VK_TAB);
	InputManager::GetInstance()->RegistKey('E');
}

void SettingsManager::SetResoultion()
{
	Vector2 vec2ScreenStartPosition = { GetSystemMetrics(SM_CXSCREEN) / 2.0f,GetSystemMetrics(SM_CYSCREEN) / 2.0f };
	Vector2 m_vec2WindowStartPosition = { vec2ScreenStartPosition.m_fx - (ConstValue::vec2BaseWindowSize.m_fx / 2.0f),
											  vec2ScreenStartPosition.m_fy - (ConstValue::vec2BaseWindowSize.m_fy / 2.0f) };

	SetWindowPos(Core::GetInstance()->GethWnd(), nullptr, m_vec2WindowStartPosition.m_fx, m_vec2WindowStartPosition.m_fy,
		ConstValue::vec2BaseWindowSize.m_fx + 16, ConstValue::vec2BaseWindowSize.m_fy + 39, SWP_SHOWWINDOW);
}

Vector2 SettingsManager::GetResolution()
{
	return ConstValue::vec2Resolution;
}
