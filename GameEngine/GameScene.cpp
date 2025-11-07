#include "pch.h"
#include "GameScene.h"
#include "Texture.h"
#include "Crew.h"
#include "Monster.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "TextureAtlas.h"

GameScene::GameScene(std::wstring _strName) : Scene(_strName)
{
	m_pBackGround = nullptr;
	m_Player = nullptr;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	srand(time(NULL));
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);
	Scene::SetSceneSize(ConstValue::vec2GameSceneSize.m_fx, ConstValue::vec2GameSceneSize.m_fy);
	Scene::SetViewPortSize(ConstValue::vec2ViewPortSize);


	Crew* pPlayer = new Crew;
	pPlayer->Init(ConstValue::vec2PlayerStartPosition);
	Scene::AddObject(pPlayer);
	m_Player = pPlayer;
	//for (int i = 0; i < 1; ++i)
	//{
	//	Monster* monster = new Monster;
	//	float x = rand() % static_cast<int>(vec2WindowSize.m_fx);
	//	float y = rand() % static_cast<int>(vec2WindowSize.m_fy);
	//	monster->Init(Vector2{ x,y });
	//	Scene::AddObject(monster, OBJECT_GROUP::MONSTER);
	//}

	//CollisionManager::GetInstance()->RegistCollisionGroup(OBJECT_GROUP::MONSTER, OBJECT_GROUP::PLAYABLE);
	//CollisionManager::GetInstance()->RegistCollisionGroup(OBJECT_GROUP::MONSTER, OBJECT_GROUP::MONSTER);
	//CollisionManager::GetInstance()->RegistCollisionGroup(OBJECT_GROUP::MONSTER, OBJECT_GROUP::PLAYER_SKILL);
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

Vector2 GameScene::GetViewPortTopLeft()
{
	if (m_Player == nullptr)
		Scene::GetViewPortTopLeft();
	Vector2 PlayerPosition = m_Player->GetPosition();
	PlayerPosition.m_fx = std::clamp(PlayerPosition.m_fx - m_vec2ViewPortSize.m_fx * 0.5f, 0.0f, m_vec2SceneSize.m_fx - m_vec2ViewPortSize.m_fx);
	PlayerPosition.m_fy = std::clamp(PlayerPosition.m_fy - m_vec2ViewPortSize.m_fy * 0.5f, 0.0f, m_vec2SceneSize.m_fy - m_vec2ViewPortSize.m_fy);
	return PlayerPosition;
}
