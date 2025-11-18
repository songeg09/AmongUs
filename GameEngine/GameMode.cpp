#include "pch.h"
#include "GameMode.h"
#include "Player.h"

GameMode::GameMode()
{
	m_Player = nullptr;
	m_UIFlags = 0;
}

GameMode::~GameMode()
{
}

void GameMode::Init(Player* _Player)
{
	m_Player = _Player;
	m_iTotalTasks = 0;			// 임시 설정
	m_iCompletedTasks = 0;
	
	m_UIFlags |= Flag(static_cast<int>(UI_TYPE::HUD));
}

void GameMode::OpenUI(int _uiIndex)
{
	switch ((UI_TYPE)_uiIndex)
	{
	case UI_TYPE::HUD:
		m_UIFlags = Flag(static_cast<int>(UI_TYPE::HUD));
		break;

	case UI_TYPE::MAP:
		static Flags mapBit = Flag(static_cast<int>(UI_TYPE::MAP));
		m_UIFlags = Flag(static_cast<int>(UI_TYPE::HUD)) | (m_UIFlags ^ mapBit) & mapBit;
		break;

	case UI_TYPE::TASK_NUMBER_SEQUNECE:
		static Flags numberSequenceBit = Flag(static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE));
		m_UIFlags = Flag(static_cast<int>(UI_TYPE::HUD)) | (m_UIFlags ^ numberSequenceBit) & numberSequenceBit;
		break;
	}
}
