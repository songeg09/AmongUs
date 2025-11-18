#include "pch.h"
#include "GameScene.h"

#include "InputManager.h"
#include "CollisionManager.h"

#include "Texture.h"
#include "TextureAtlas.h"

#include "GameMode.h"

#include "Player.h"
#include "Monster.h"
#include "GameObject.h"

#include "MapUI.h"
#include "PlayerStatusUI.h"
#include "NumberSequenceTask.h"

GameScene::GameScene(std::wstring _strName) : Scene(_strName)
{
	m_GameMode = nullptr;
	m_pBackGround = nullptr;
	m_Player = nullptr;
	m_UIFlags = 0;
}

GameScene::~GameScene()
{
	delete m_GameMode;
}

void GameScene::Init()
{
	srand(time(NULL));

	// 배경화면 설정
	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);
	
	// Scene 크기 설정
	ConfigureRenderSurface(
		Vector2(m_pBackGround->GetWidth(), m_pBackGround->GetHeight()),
		ConstValue::fGameSceneGaurdBandPx
	);

	// 1. 플레이어 생성 및 오브젝트 생성
	Player* pPlayer = new Player;
	Vector2 PlayerStart(m_pBackGround->GetWidth() / 2, m_pBackGround->GetHeight() / 2);
	pPlayer->Init(PlayerStart, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::MAP)));
	Scene::AddObject(pPlayer);
	m_Player = pPlayer;

	// 2. GameMode 생성
	m_GameMode = new GameMode;
	m_GameMode->Init(m_Player);

	// 3. 오브젝트 생성
	GameObject* gameObject = new GameObject;
	gameObject->Init(m_Player->GetPosition(), Vector2(10, 10), std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE)));
	Scene::AddObject(gameObject);

	// UI 생성
	m_UIFlags |= Flag(static_cast<int>(UI_TYPE::HUD));
	m_PrevUIFlags = m_UIFlags;
	m_arrUIs.resize(static_cast<int>(UI_TYPE::END));
	
	// UI z축 순서에 맞게 생성 필요!
	PlayerStatusUI* playerUI= new PlayerStatusUI;
	playerUI->Init(m_GameMode, m_Player, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::MAP)));
	playerUI->SetVisibility(true);
	m_arrUIs[static_cast<int>(UI_TYPE::HUD)] = playerUI;

	
	MapUI* mapUI = new MapUI;
	mapUI->Init(m_Player, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD)));
	m_arrUIs[static_cast<int>(UI_TYPE::MAP)] = mapUI;

	NumberSequenceTask* Task1 = new NumberSequenceTask;
	Task1->Init(
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::WORKING); },
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE); },
		nullptr, 
		nullptr,
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE)] = Task1;

	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::WALL_DETECTOR, COLLISION_TAG::WALL);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::PLAYER_HURTBOX, COLLISION_TAG::MONSTER_PLAYER_DETECTOR);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::PLAYER_HURTBOX, COLLISION_TAG::MONSTER_ATTACK_RANGE);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::PLAYER_INTERACTION, COLLISION_TAG::OBJECT_INTERACTION_DETECTOR);
}

void GameScene::Update()
{
	Scene::Update();
}

void GameScene::Render(HDC _memDC)
{
	// 1. 배경 그리기
	Vector2 BackBufferTopLeftInScene = GetBackBufferTopLeftInScene();
	BitBlt(_memDC, 0, 0, m_vec2BackBufferSize.m_fx, m_vec2BackBufferSize.m_fy,
		m_pBackGround->GetDC(), BackBufferTopLeftInScene.m_fx, BackBufferTopLeftInScene.m_fy, SRCCOPY);

	// 2. 오브젝트 그리기 및 UI 그리기
	Scene::Render(_memDC);
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

void GameScene::OpenUI(int _flagIndex)
{
	static Flags mapBit = Flag(static_cast<int>(UI_TYPE::MAP));

	switch (static_cast<UI_TYPE>(_flagIndex))
	{
	case UI_TYPE::HUD:
		m_UIFlags = Flag(static_cast<int>(UI_TYPE::HUD));
		break;

	case UI_TYPE::MAP:
		m_UIFlags = (m_UIFlags ^ mapBit) & mapBit |  Flag(static_cast<int>(UI_TYPE::HUD));
		break;

	case UI_TYPE::TASK_NUMBER_SEQUNECE:
		OpenTask(_flagIndex);
		break;
	}
}

void GameScene::OpenTask(int _flagIndex)
{
	static Flags numberSequenceBit = Flag(static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE));

	if (m_Player->GetCharacterState() == Player::CHARACTER_STATE::WORKING)
		return;

	switch ((UI_TYPE)_flagIndex)
	{
	case UI_TYPE::TASK_NUMBER_SEQUNECE:
		m_UIFlags = (m_UIFlags ^ numberSequenceBit) & numberSequenceBit | Flag(static_cast<int>(UI_TYPE::HUD));
		break;
	}
}
