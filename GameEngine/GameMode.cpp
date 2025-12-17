#include "pch.h"
#include "GameMode.h"
#include "IMinimapProvider.h"
#include "Player.h"


GameMode::GameMode()
{	
}

GameMode::~GameMode()
{
}

void GameMode::Init(std::shared_ptr<Player> _Player, std::shared_ptr<IMinimapProvider> _MinimapProvider)
{
	m_MinimapProvider = _MinimapProvider;
	m_Player = _Player;
	m_iTotalTasks = m_MinimapProvider.lock()->GetGameObjects().size();
	m_eState = GAME_STATE::PLAYING;
}

void GameMode::Update()
{
	if (m_Player.lock()->GetCharacterState() == Player::CHARACTER_STATE::DEAD)
		m_eState = GAME_STATE::LOSE;

	else if (GetProgress() == 1.0f)
		m_eState = GAME_STATE::WIN;
}

float GameMode::GetProgress()
{
	if (m_iTotalTasks == 0)
		return 1.0f;
	return (float)(m_iTotalTasks - m_MinimapProvider.lock()->GetGameObjects().size()) / (float)m_iTotalTasks;
}


