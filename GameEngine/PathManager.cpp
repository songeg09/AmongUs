#include "pch.h"
#include "PathManager.h"

PathManager::PathManager() : m_szContentsPath{}
{

}
PathManager::~PathManager()
{

}
void PathManager::Init()
{
	GetCurrentDirectoryW(sizeof(m_szContentsPath), m_szContentsPath);
	int length = wcslen(m_szContentsPath);
	int i = length - 1;
	while (m_szContentsPath[i] != L'\\') { --i; }
	m_szContentsPath[i] = NULL;
	wcscat_s(m_szContentsPath, ConstValue::strResourcePath.c_str());
}
