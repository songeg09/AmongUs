#include "pch.h"
#include "GameMode.h"
#include "GameScene.h"
#include "Player.h"

GameMode::GameMode()
{
	m_Player = nullptr;
	m_GameScene = nullptr;
}

GameMode::~GameMode()
{
}

void GameMode::Init(Player* _Player, GameScene* _GameScene, int _iTotalTasks)
{
	m_Player = _Player;
	m_GameScene = _GameScene;
	m_iTotalTasks = _iTotalTasks;
	m_iCompletedTasks = 0;
}

void GameMode::ChangeUI(int _uiIndex)
{
	switch ((GameScene::UI_MODE)_uiIndex)
	{
	case GameScene::UI_MODE::HUD:
		break;
	case GameScene::UI_MODE::MAP:
		break;
	}
}

void GameMode::OpenMapUI()
{
	if (m_Player->GetCharacterState() == Player::CHARACTER_STATE::NONE)
	{
		m_GameScene->ChangeUI(GameScene::UI_MODE::MAP);
		m_Player->SetCharacterState(Player::CHARACTER_STATE::MAP);
	}
}

void GameMode::OpenHUDUI()
{
	m_GameScene->ChangeUI(GameScene::UI_MODE::HUD);
	m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE);
}





