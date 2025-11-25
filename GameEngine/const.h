#pragma once
#include<string>
namespace ConstValue
{
	static const std::wstring strResourcePath = L"\\bin\\content\\";
	static const std::wstring strTexturePath = L"texture\\";
	static const std::wstring strDataPath = L"data\\";

	static const Vector2 vec2BaseWindowSize = { 1280.0f, 720.0f };

	static const Vector2 vec2ViewPortSize = { 1024.0f,576.0f };
	static const Vector2 vec2Resolution = { 1024.0f,576.0f };
	static const float fGameSceneGaurdBandPx = 128;

	static const Vector2 vec2GameSceneSize = { 1000.0f,1000.0f };
	static const Vector2 vec2PlayerStartPosition = { vec2GameSceneSize.m_fx * 0.5f,vec2GameSceneSize.m_fy * 0.5f };
	static const float fFrictionCoefficient = 3.0f;
	static const std::wstring strDataTableNamesFileName = L"DataTableNames.txt";
	static const std::wstring strSettingsTableFileName = L"Settings.txt";


	// 오브젝트 사이즈
	static const Vector2 vec2VentSize = { 20.0f, 15.0f };

	static const float fMaxUploadTime = 10.0f;
	
	
	static const float fGhostProximityRange = 20.0f;
	static const float fGhostSearchTime = 5.0f;
	static const float fGhostSearchRange = 400.0f;

}