#include "pch.h"
#include "GameScene.h"
#include "Texture.h"
#include "Player.h"
#include "Monster.h"
#include "InputManager.h"
#include "CollisionManager.h"

GameScene::GameScene(std::wstring _strName) : Scene(_strName)
{
	m_pBackGround = nullptr;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	srand(time(NULL));
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);
	Scene::SetWindowSize(ConstValue::vec2GameSceneWindowSize.m_fx, ConstValue::vec2GameSceneWindowSize.m_fy);

	Player* pPlayer = new Player;
	Vector2 vec2WindowSize = Scene::GetWindowSize();
	pPlayer->Init(ConstValue::vec2PlayerStartPosition);
	Scene::AddObject(pPlayer, OBJECT_GROUP::PLAYABLE);
	for (int i = 0; i < 1; ++i)
	{
		Monster* monster = new Monster;
		float x = rand() % static_cast<int>(vec2WindowSize.m_fx);
		float y = rand() % static_cast<int>(vec2WindowSize.m_fy);
		monster->Init(Vector2{ x,y });
		Scene::AddObject(monster, OBJECT_GROUP::MONSTER);
	}

	CollisionManager::GetInstance()->RegistCollisionGroup(OBJECT_GROUP::MONSTER, OBJECT_GROUP::PLAYABLE);
	CollisionManager::GetInstance()->RegistCollisionGroup(OBJECT_GROUP::MONSTER, OBJECT_GROUP::MONSTER);
	CollisionManager::GetInstance()->RegistCollisionGroup(OBJECT_GROUP::MONSTER, OBJECT_GROUP::PLAYER_SKILL);
}

void GameScene::Update()
{
	Scene::Update();
}

void GameScene::Render(HDC _memDC)
{
	BitBlt(_memDC, 0, 0, m_pBackGround->GetWidth(), m_pBackGround->GetHeight(),
		m_pBackGround->GetDC(), 0, 0, SRCCOPY);
	Scene::Render(_memDC);
}