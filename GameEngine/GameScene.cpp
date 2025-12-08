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
#include "Wall.h"

#include "MenuUI.h"
#include "MapUI.h"
#include "PlayerStatusUI.h"
#include "GameResultUI.h"
#include "NumberSequenceTask.h"
#include "DataUploadTask.h"
#include "TimedButtonsTask.h"

#include "MinimapProvider.h"
#include "Interactable.h"
#include "Attemptable.h"
#include "MapInfo.h"

GameScene::GameScene(std::wstring _strName) : Scene(_strName)
{
	m_UIFlags = 0;
}

GameScene::~GameScene()
{
}

void GameScene::Release()
{
	Scene::Release();

	m_GameMode = nullptr;
	m_Player = nullptr;
	m_arrGhosts.clear();
	m_arrGameObjects.clear();
	m_arrVents.clear();
	m_setTasksLeft.clear();
}

void GameScene::Init()
{
	Scene::Init();

	// 배경화면 설정
	m_pBackGround = ResourceManager::GetInstance()->LoadTexture(TEXTURE_TYPE::BACKGROUND);

	// Scene 크기 설정
	ConfigureRenderSurface(
		Vector2(m_pBackGround.lock()->GetWidth(), m_pBackGround.lock()->GetHeight()),
		ConstValue::fGameSceneGaurdBandPx
	);

	InstantiateObjects();

	// 게임 모드 생성
	m_GameMode = std::make_shared<GameMode>();
	m_GameMode->Init(m_Player, shared_from_this());

	// UI 생성
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
}

void GameScene::Render(HDC _memDC)
{
	// 1. 배경 그리기
	Vector2 BackBufferTopLeftInScene = GetBackBufferTopLeftInScene();
	BitBlt(_memDC, 0, 0, m_vec2BackBufferSize.m_fx, m_vec2BackBufferSize.m_fy,
		m_pBackGround.lock()->GetDC(), BackBufferTopLeftInScene.m_fx, BackBufferTopLeftInScene.m_fy, SRCCOPY);

	// 2. 오브젝트 그리기 및 UI 그리기
	Scene::Render(_memDC);
}


void GameScene::InitUI()
{
	m_arrUIs.resize(static_cast<int>(UI_TYPE::END));

	// UI z축 순서에 맞게 생성 필요!
	std::unique_ptr<PlayerStatusUI> playerUI = std::make_unique<PlayerStatusUI>();
	playerUI->Init(
		m_GameMode, 
		m_Player, 
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::MAP)),
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::MENU))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::HUD)] = std::move(playerUI);

	std::unique_ptr<MapUI> mapUI = std::make_unique<MapUI>();
	mapUI->Init(shared_from_this(), std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD)));
	m_arrUIs[static_cast<int>(UI_TYPE::MAP)] = std::move(mapUI);

	std::unique_ptr<MenuUI> menuUI = std::make_unique<MenuUI>();
	menuUI->Init(
		std::bind(&SceneManager::RequestSceneChange, SceneManager::GetInstance(), SCENE_TYPE::GAME),
		std::bind(&SceneManager::RequestSceneChange, SceneManager::GetInstance(), SCENE_TYPE::TITLE)
	);
	m_arrUIs[static_cast<int>(UI_TYPE::MENU)] = std::move(menuUI);

	std::unique_ptr<GameResultUI> resultUI = std::make_unique<GameResultUI>();
	resultUI->Init(
		m_GameMode,
		std::bind(&SceneManager::RequestSceneChange, SceneManager::GetInstance(), SCENE_TYPE::GAME),
		std::bind(&SceneManager::RequestSceneChange, SceneManager::GetInstance(), SCENE_TYPE::TITLE)
	);
	m_arrUIs[static_cast<int>(UI_TYPE::RESULT)] = std::move(resultUI);

	// Task UI 생성
	std::unique_ptr<NumberSequenceTask> Task1 = std::make_unique<NumberSequenceTask>();
	Task1->Init(
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::WORKING); },
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE); },
		std::bind(&GameScene::OnTaskSuccess, this), 
		std::bind(&GameScene::OnTaskFail, this),
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE)] = std::move(Task1);

	std::unique_ptr<DataUploadTask> Task2 = std::make_unique<DataUploadTask>();
	Task2->Init(
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::WORKING); },
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE); },
		std::bind(&GameScene::OnTaskSuccess, this),
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::TASK_DATA_UPLOAD)] = std::move(Task2);

	std::unique_ptr<TimedButtonsTask> Task3 = std::make_unique<TimedButtonsTask>();
	Task3->Init(
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::WORKING); },
		[this]() {m_Player->SetCharacterState(Player::CHARACTER_STATE::NONE); },
		std::bind(&GameScene::OnTaskSuccess, this),
		std::bind(&GameScene::OnTaskFail, this),
		std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::HUD))
	);
	m_arrUIs[static_cast<int>(UI_TYPE::TASK_TIMED_BUTTONS)] = std::move(Task3);
}

void GameScene::InstantiateObjects()
{
	MapInfo mapInfo;
	mapInfo.Load();

	// Player
	m_Player = std::make_shared<Player>();
	m_Player->Init(mapInfo.m_vec2PlayerStart, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::MAP)));

	// Ghosts
	for (int i = 0; i < ConstValue::iNumOfGhosts; ++i)
	{
		std::shared_ptr<Ghost> ghost = std::make_shared<Ghost>();
		ghost->Init(mapInfo.m_arrWayPoints);
		m_arrGhosts.push_back(ghost);

	}

	// Wall
	for (int i = 0; i < mapInfo.m_arrAllWallVertices.size(); ++i)
	{
		if (mapInfo.m_arrAllWallVertices[i].size() < 2)
			continue;
		for (int j = 0; j < mapInfo.m_arrAllWallVertices[i].size()-1; ++j)
			CreateWall(mapInfo.m_arrAllWallVertices[i][j], mapInfo.m_arrAllWallVertices[i][j + 1]);
	}

	// Vent
	m_arrVents.reserve(mapInfo.m_arrVent.size());
	for (const Vector2& pos : mapInfo.m_arrVent)
	{
		std::shared_ptr<Vent> vent = std::make_shared<Vent>();
		vent->Init(pos);
		m_arrVents.push_back(vent);
	}

	// Number Sequnece
	m_arrGameObjects.reserve(mapInfo.m_arrNumberSequencePos.size() + mapInfo.m_arrDataUploadPos.size() + mapInfo.m_arrTimedButtonsPos.size());
	for (const Vector2& pos : mapInfo.m_arrNumberSequencePos)
	{
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
		gameObject->Init(pos, ConstValue::vec2TaskSize, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::TASK_NUMBER_SEQUNECE)));
		m_setTasksLeft.insert(gameObject.get());
		m_arrGameObjects.push_back(gameObject);
	}

	// Data Upload
	for (const Vector2& pos : mapInfo.m_arrDataUploadPos)
	{
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
		gameObject->Init(pos, ConstValue::vec2TaskSize, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::TASK_DATA_UPLOAD)));
		m_setTasksLeft.insert(gameObject.get());
		m_arrGameObjects.push_back(gameObject);
	}

	// Timed Buttons
	for (const Vector2& pos : mapInfo.m_arrTimedButtonsPos)
	{
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
		gameObject->Init(pos, ConstValue::vec2TaskSize, std::bind(&GameScene::OpenUI, this, static_cast<int>(UI_TYPE::TASK_TIMED_BUTTONS)));
		m_setTasksLeft.insert(gameObject.get());
		m_arrGameObjects.push_back(gameObject);
	}
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
	static Flags menuBit = Flag(static_cast<int>(UI_TYPE::MENU));

	switch (static_cast<UI_TYPE>(_flagIndex))
	{
	case UI_TYPE::HUD:
		m_UIFlags = Flag(static_cast<int>(UI_TYPE::HUD));
		break;

	case UI_TYPE::MENU:
		m_UIFlags = ((m_UIFlags ^ menuBit) & menuBit) | Flag(static_cast<int>(UI_TYPE::HUD));
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
	if (Attemptable* task = dynamic_cast<Attemptable*>(m_Player->GetInteractableObject()))
	{
		task->OnSuccess();
		m_setTasksLeft.erase(task);
	}
	OpenUI(static_cast<int>(UI_TYPE::HUD));
}

void GameScene::OnTaskFail()
{
	if (Attemptable* task = dynamic_cast<Attemptable*>(m_Player->GetInteractableObject()))
		task->OnFail();
	OpenUI(static_cast<int>(UI_TYPE::HUD));
}
