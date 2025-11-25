#include "pch.h"
#include "GameMode.h"
#include "MinimapProvider.h"
#include "Player.h"


GameMode::GameMode()
{	
	m_Player = nullptr;
	m_MinimapProvider = nullptr;
}

GameMode::~GameMode()
{
}

void GameMode::Init(Player* _Player, MinimapProvider* _MinimapProvider)
{
	m_MinimapProvider = _MinimapProvider;
	m_Player = _Player;
	m_iTotalTasks = m_MinimapProvider->GetGameObjects().size();
	m_eState = GAME_STATE::PLAYING;
}

void GameMode::Update()
{
	if (m_Player->GetCharacterState() == Player::CHARACTER_STATE::DEAD)
		m_eState = GAME_STATE::LOSE;

	else if (GetProgress() == 1.0f)
		m_eState = GAME_STATE::WIN;
}

float GameMode::GetProgress()
{
	if (m_iTotalTasks == 0)
		return 1.0f;
	return (float)(m_iTotalTasks - m_MinimapProvider->GetGameObjects().size()) / (float)m_iTotalTasks;
}


