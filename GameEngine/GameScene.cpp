#include "pch.h"
#include "GameScene.h"
#include "Texture.h"
#include "Player.h"
#include "Monster.h"
#include "Vent.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "TextureAtlas.h"
#include "Wall.h"

#include "MapUI.h"
#include "PlayerHUD.h"

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

	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);
	ConfigureRenderSurface(
		Vector2(m_pBackGround->GetWidth(), m_pBackGround->GetHeight()),
			ConstValue::fGameSceneGaurdBandPx
	);

	m_eCurUI = UI_MODE::HUD;
	m_arrUIs[UI_MODE::HUD] = new PlayerHUD;
	m_arrUIs[UI_MODE::HUD]->Init();
	m_arrUIs[UI_MODE::MAP] = new MapUI;
	m_arrUIs[UI_MODE::MAP]->Init();

	// 플레이어 생성
	Player* pPlayer = new Player;
	Vector2 PlayerStart(m_pBackGround->GetWidth() / 2, m_pBackGround->GetHeight() / 2);
	pPlayer->Init(PlayerStart);
	Scene::AddObject(pPlayer);
	m_Player = pPlayer;

	//Monster* pMonster = new Monster;
	//PlayerStart.m_fx += 200;
	//pMonster->Init(PlayerStart);
	//Scene::AddObject(pMonster);

	Vent* vent = new Vent;
	PlayerStart.m_fx += 200;
	vent->Init(PlayerStart);
	Scene::AddObject(vent);

	// 벽 생성
	//Wall* wall = new Wall;
	//wall->Init();
	//Scene::AddObject(wall);
	
	//for (int i = 0; i < 1; ++i)
	//{
	//	Monster* monster = new Monster;
	//	float x = rand() % static_cast<int>(vec2WindowSize.m_fx);
	//	float y = rand() % static_cast<int>(vec2WindowSize.m_fy);
	//	monster->Init(Vector2{ x,y });
	//	Scene::AddObject(monster, OBJECT_GROUP::MONSTER);
	//}

	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::WALL_DETECTOR, COLLISION_TAG::WALL);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::PLAYER_HURTBOX, COLLISION_TAG::MONSTER_PLAYER_DETECTOR);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::PLAYER_HURTBOX, COLLISION_TAG::MONSTER_ATTACK_RANGE);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::PLAYER_INTERACTION, COLLISION_TAG::OBJECT_INTERACTION_DETECTOR);

}

void GameScene::Update()
{
	Scene::Update();
	m_arrUIs[m_eCurUI]->Update();
}

void GameScene::Render(HDC _memDC)
{
	// 1. 배경 그리기
	Vector2 BackBufferTopLeftInScene = GetBackBufferTopLeftInScene();
	BitBlt(_memDC, 0, 0, m_vec2BackBufferSize.m_fx, m_vec2BackBufferSize.m_fy,
		m_pBackGround->GetDC(), BackBufferTopLeftInScene.m_fx, BackBufferTopLeftInScene.m_fy, SRCCOPY);

	// 2. 오브젝트 그리기
	Scene::Render(_memDC);

	// 3. UI 그리기
	m_arrUIs[m_eCurUI]->Render(_memDC);
}

Vector2 GameScene::GetViewPortTopLeftInScene()
{

	assert(m_Player != nullptr);
	Vector2 PlayerPosition = m_Player->GetPosition();
	PlayerPosition.m_fx = std::clamp(PlayerPosition.m_fx - ConstValue::vec2BaseWindowSize.m_fx * 0.5f, 0.0f, m_vec2SceneSize.m_fx - ConstValue::vec2BaseWindowSize.m_fx);
	PlayerPosition.m_fy = std::clamp(PlayerPosition.m_fy - ConstValue::vec2BaseWindowSize.m_fy * 0.5f, 0.0f, m_vec2SceneSize.m_fy - ConstValue::vec2BaseWindowSize.m_fy);
	return PlayerPosition;
	return Vector2(0, 0);
}

Vector2 GameScene::GetBackBufferTopLeftInScene()
{
	Vector2 BackBufferTopLeftInScene = GetViewPortTopLeftInScene();
	BackBufferTopLeftInScene.m_fx -= m_fGuardBandPx;
	BackBufferTopLeftInScene.m_fy -= m_fGuardBandPx;

	return BackBufferTopLeftInScene;
}
