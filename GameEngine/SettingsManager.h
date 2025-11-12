#pragma once
class SettingsManager
{
	SINGLETON(SettingsManager);
public:
	void Init();
	void SetResoultion();
	Vector2 GetResolution();
};

