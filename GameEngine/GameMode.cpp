#include "pch.h"
#include "GameMode.h"
#include "Player.h"

GameMode::GameMode()
{
	m_Player = nullptr;
	
}

GameMode::~GameMode()
{
}

void GameMode::Init(Player* _Player)
{
	m_Player = _Player;
	m_iTotalTasks = 0;			// 임시 설정
	m_iCompletedTasks = 0;
}


