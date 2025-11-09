#pragma once
#include<string>
namespace ConstValue
{
	static const std::wstring strResourcePath = L"\\bin\\content\\";
	static const std::wstring strTexturePath = L"texture\\";
	static const std::wstring strDataPath = L"data\\";
	static const Vector2 vec2ViewPortSize = { 1440.0f,1000.0f };
	static const Vector2 vec2GameSceneSize = { 1000.0f,1000.0f };
	static const Vector2 vec2PlayerStartPosition = { vec2GameSceneSize.m_fx * 0.5f,vec2GameSceneSize.m_fy * 0.5f };
	static const float fFrictionCoefficient = 3.0f;
	static const std::wstring strDataTableNamesFileName = L"DataTableNames.txt";

}