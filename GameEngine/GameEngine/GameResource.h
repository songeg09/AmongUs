#pragma once
class GameResource
{
private:
	std::wstring m_strKey;
	std::wstring m_strRelativePath;
public:
	void SetKey(std::wstring _strKey) { m_strKey = _strKey; }
	void SetRelativePath(std::wstring _strRelativePath) { m_strRelativePath = _strRelativePath; }

	const std::wstring& GetKey() { return m_strKey; }
	const std::wstring& GetRelativePath() { return m_strRelativePath; }
	GameResource();
	~GameResource();
};

