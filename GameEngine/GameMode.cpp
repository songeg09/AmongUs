#include "pch.h"
#include "GameMode.h"
#include "MinimapProvider.h"


GameMode::GameMode()
{	
}

GameMode::~GameMode()
{
}

void GameMode::Init(MinimapProvider* _MinimapProvider)
{
	m_MinimapProvider = _MinimapProvider;
	m_iTotalTasks = m_MinimapProvider->GetGameObjects().size();
}

void GameMode::Update()
{
	
}

float GameMode::GetProgress()
{
	if (m_iTotalTasks == 0)
		return 1.0f;
	return (float)(m_iTotalTasks - m_MinimapProvider->GetGameObjects().size()) / (float)m_iTotalTasks;
}


