#pragma once
class PathManager
{
	SINGLETON(PathManager)
private:
	WCHAR m_szContentsPath[512];
public:
	void Init();
	const WCHAR* GetContentpath() { return m_szContentsPath; }
};

