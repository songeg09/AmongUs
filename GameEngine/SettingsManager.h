#pragma once
class SettingsManager
{
	SINGLETON(SettingsManager);
public:
	void Init();
	void Update();
	void SetResoultion();
	Vector2 GetResolution();
};

