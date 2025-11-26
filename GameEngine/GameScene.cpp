#include "pch.h"
#include "GameScene.h"
#include "GameMode.h"

#include "InputManager.h"
#include "CollisionManager.h"
#include "SceneManager.h"

#include "Texture.h"
#include "TextureAtlas.h"

#include "Player.h"
#include "Ghost.h"
#include "GameObject.h"
#include "Vent.h"
#include "CircleZone.h"

#include "MapUI.h"
#include "PlayerStatusUI.h"
#include "GameResultUI.h"
#include "NumberSequenceTask.h"
#include "DataUploadTask.h"
#include "TimedButtonsTask.h"

#include "MinimapProvider.h"
#include "Interactable.h"

GameScene::GameScene(std::wstring _strName) : Scene(_strName)
{
	m_pBackGround = nullptr;
	m_Player = nullptr;
	m_UIFlags = 0;
	m_GlobalSoundZone = nullptr;
	m_GameMode = nullptr;
}

GameScene::~GameScene()
{
}

void GameScene::Release()
{
	if (m_GameMode != nullptr)
		delete m_GameMode;

	Scene::Release();
}

void GameScene::Init()
{
	Scene::Init();

	// 배경화면 설정
	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);

	// Scene 크기 설정
	ConfigureRenderSurface(
		Vector2(m_pBackGround->GetWidth(), m_pBackGround->GetHeight()),
		ConstValue::fGameSceneGaurdBandPx
	);

	// 1. 플레이어 생성 및 오브젝트 생성
	m_Player = new Player;
	Vector2 PlayerStart(m_pBackGround->GetWidth() / 2, m_pBackGround->GetHeight() / 2);
	m_Player->Init(PlayerStart, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::MAP)));
	Scene::AddObject(m_Player);

	std::vector<Vector2> tmpWayPoints = { Vector2(500,500), Vector2(2000, 500), Vector2(5000, 3000) };
	Vector2 Pos = m_Player->GetPosition();
	Pos.m_fx += 1000.0f;
	m_Ghost = new Ghost;
	m_Ghost->Init(Pos, tmpWayPoints);
	Scene::AddObject(m_Ghost);

	m_GlobalSoundZone = new CircleZone;
	m_GlobalSoundZone->Init(COLLISION_TAG::SOUND, 30.0f);
	m_GlobalSoundZone->SetEnable(false);
	Scene::AddObject(m_GlobalSoundZone);

	// 2. 오브젝트 생성
	Vent* vent = new Vent;
	vent->Init(m_Player->GetPosition());
	Scene::AddObject(vent);

	//GameObject* gameObject = new GameObject;
	//gameObject->Init(m_Player->GetPosition(), Vector2(10, 10), std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE)));
	//Scene::AddObject(gameObject);
	//m_setTasksLeft.insert(gameObject);

	Pos.m_fx += 100;
	Pos.m_fy += 500;
	GameObject* gameObject2 = new GameObject;
	gameObject2->Init(Pos, Vector2(10, 10), std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::TASK_DATA_UPLOAD)));
	Scene::AddObject(gameObject2);
	m_setTasksLeft.insert(gameObject2);

	Pos.m_fx += 100;
	Pos.m_fy += 500;
	GameObject* gameObject3 = new GameObject;
	gameObject3->Init(Pos, Vector2(10, 10), std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::TASK_TIMED_BUTTONS)));
	Scene::AddObject(gameObject3);
	m_setTasksLeft.insert(gameObject3);

	// 3. 게임 모드 생성
	m_GameMode = new GameMode;
	m_GameMode->Init(m_Player, this);

	// 4. UI 생성
	m_UIFlags = Flag(static_cast<int>(UI_TYPE::HUD));
	InitUI();

	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::WALL_DETECTOR, COLLISION_TAG::WALL);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::PLAYER_INTERACTION, COLLISION_TAG::OBJECT_INTERACTION_DETECTOR);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::GHOST_SIGHT_SENSOR, COLLISION_TAG::PLAYER_HURTBOX);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::GHOST_CHASING_SENSOR, COLLISION_TAG::PLAYER_HURTBOX);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::GHOST_ATTACK_RANGE, COLLISION_TAG::PLAYER_HURTBOX);
	CollisionManager::GetInstance()->RegistCollisionGroup(COLLISION_TAG::GHOST_HEARING_SENSOR, COLLISION_TAG::SOUND);
}


void GameScene::Update()
{
	Scene::Update();
	m_GameMode->Update();

	if (m_GameMode->GetGameState() != GameMode::GAME_STATE::PLAYING)
		OpenUI(static_cast<int>(UI_TYPE::RESULT));

	if (m_GlobalSoundZone->GetEnbale() == true && Vector2::Distance(m_GlobalSoundZone->GetPosition(), m_Ghost->GetPosition()) < ConstValue::fGhostProximityRange)
		m_GlobalSoundZone->SetEnable(false);
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

void GameScene::InitUI()
{
	m_arrUIs.resize(static_cast<int>(UI_TYPE::END));

	// UI z축 순서에 맞게 생성 필요!
	PlayerStatusUI* playerUI = new PlayerStatusUI;
	playerUI->Init(m_GameMode, m_Player, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::MAP)));
	playerUI->SetVisibility(true);
	m_arrUIs[static_cast<int>(UI_TYPE::HUD)] = playerUI;

	MapUI* mapUI = new MapUI;
	mapUI->Init(dynamic_cast<MinimapProvider*>(this), std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD)));
	m_arrUIs[static_cast<int>(UI_TYPE::MAP)] = mapUI;

	GameResultUI* resultUI = new GameResultUI;
	resultUI->Init(
		m_GameMode, 
		nullptr, 
		std::bind(&SceneManager::RequestSceneChange, SceneManager::GetInstance(), SCENE_TYPE::TITLE)
	);
	m_arrUIs[static_cast<int>(UI_TYPE::RESULT)] = resultUI;

	// Task UI 생성
	NumberSequenceTask* Task1 = new NumberSequenceTask;
	Task1->Init(
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::WORKING); },
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE); },
		std::bind(&GameScene::OnTaskSuccess, this), 
		std::bind(&GameScene::OnTaskFail, this),
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE)] = Task1;

	DataUploadTask* Task2 = new DataUploadTask;
	Task2->Init(
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::WORKING); },
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE); },
		std::bind(&GameScene::OnTaskSuccess, this),
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::TASK_DATA_UPLOAD)] = Task2;

	TimedButtonsTask* Task3 = new TimedButtonsTask;
	Task3->Init(
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::WORKING); },
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE); },
		std::bind(&GameScene::OnTaskSuccess, this),
		std::bind(&GameScene::OnTaskFail, this),
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::TASK_TIMED_BUTTONS)] = Task3;
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
		m_UIFlags = ((m_UIFlags ^ mapBit) & mapBit) |  Flag(static_cast<int>(UI_TYPE::HUD));
		break;

	case UI_TYPE::RESULT:
		m_UIFlags = Flag(static_cast<int>(UI_TYPE::RESULT));
		break;

	default:
		OpenTask(_flagIndex);
		break;
	}
}

void GameScene::OpenTask(int _flagIndex)
{
	static Flags numberSequenceBit = Flag(static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE));
	static Flags dataUploadBit = Flag(static_cast<int>(UI_TYPE::TASK_DATA_UPLOAD));
	static Flags timedbuttonsBit = Flag(static_cast<int>(UI_TYPE::TASK_TIMED_BUTTONS));

	switch ((UI_TYPE)_flagIndex)
	{
	case UI_TYPE::TASK_NUMBER_SEQUNECE:
		m_UIFlags = (m_UIFlags ^ numberSequenceBit) & numberSequenceBit | Flag(static_cast<int>(UI_TYPE::HUD));
		break;
	case UI_TYPE::TASK_DATA_UPLOAD:
		m_UIFlags = (m_UIFlags ^ dataUploadBit) & dataUploadBit | Flag(static_cast<int>(UI_TYPE::HUD));
		break;
	case UI_TYPE::TASK_TIMED_BUTTONS:
		m_UIFlags = (m_UIFlags ^ timedbuttonsBit) & timedbuttonsBit | Flag(static_cast<int>(UI_TYPE::HUD));
		break;
	}
}

Vector2 GameScene::GetPlayerPos() const
{
	return m_Player->GetPosition();
}

void GameScene::OnTaskSuccess()
{
	m_Player->GetInteractableObject()->OnSuccess();
	m_setTasksLeft.erase(m_Player->GetInteractableObject());
	OpenUI(static_cast<int>(UI_TYPE::HUD));
}

void GameScene::OnTaskFail()
{
	m_GlobalSoundZone->SetEnable(true);
	m_GlobalSoundZone->SetPosition(m_Player->GetInteractableObject()->GetPosition());
	OpenUI(static_cast<int>(UI_TYPE::HUD));
}
