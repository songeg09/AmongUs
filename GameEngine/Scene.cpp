#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Core.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "UI.h"
#include "Wall.h"
#include "WallDetector.h"
#include "GDIManager.h"

Scene::Scene(std::wstring _strName)
{
	m_strName = _strName;
	m_UIFlags = 0;
	m_PrevUIFlags = 0;
}

Scene::~Scene()
{
	Release();
}

void Scene::Release()
{
	CollisionManager::GetInstance()->ReleaseCollisionGroup();

	m_arrUIs.clear();
	m_listWalls.clear();
}

void Scene::Init()
{
	m_UIFlags = 0;
	m_PrevUIFlags = 0;
}

void Scene::ConfigureRenderSurface(Vector2 _vec2SceneSize, float _fGuardBandPx)
{
	m_vec2SceneSize = _vec2SceneSize;
	m_fGuardBandPx = _fGuardBandPx;
	
	m_vec2BackBufferSize = ConstValue::vec2BaseWindowSize;
	m_vec2BackBufferSize.m_fx += _fGuardBandPx * 2;
	m_vec2BackBufferSize.m_fy += _fGuardBandPx * 2;
}

void Scene::OpenUI(int _flagIndex)
{
	m_UIFlags |= Flag(_flagIndex);
}


void Scene::AddObject(Object* _object)
{
	m_listObjects.push_back(_object);
}

void Scene::CreateWall(Vector2 _vec2Start, Vector2 _vec2End)
{
	std::unique_ptr<Wall> wall = std::make_unique<Wall>();
	wall->Init(_vec2Start, _vec2End);
	m_listWalls.push_back(std::move(wall));
}

void Scene::RegisterWallDetector(std::shared_ptr<WallDetector> _wallDetector)
{
	m_setWallDetectors.insert(_wallDetector);
}

void Scene::UnregisterWallDetector(std::shared_ptr<WallDetector> _wallDetector)
{
	if (m_setWallDetectors.find(_wallDetector) != m_setWallDetectors.end())
		m_setWallDetectors.erase(_wallDetector);
}


void Scene::Update()
{
	for (Object* object: m_listObjects)
		object->Update();

	for (std::weak_ptr<WallDetector> detector : m_setWallDetectors)
		detector.lock()->Update();

	for (std::unique_ptr<Wall>& wall : m_listWalls)
	{
		for (std::weak_ptr<WallDetector> detector : m_setWallDetectors)
			wall->ResolvePenetration(detector.lock().get());
	}

	for (std::unique_ptr<UI>& ui : m_arrUIs)
		ui->Update();

	UpdateUIVisibility();
}

void Scene::UpdateUIVisibility()
{
	for (int i = 0; i < m_arrUIs.size(); ++i)
	{
		if ((m_UIFlags & Flag(i)) == ((m_PrevUIFlags & Flag(i))))
			continue;
		else if ((m_UIFlags & Flag(i)) != 0)
			m_arrUIs[i]->Open();
		else
			m_arrUIs[i]->Close();
	}

	m_PrevUIFlags = m_UIFlags;
}

void Scene::LateUpdate()
{
	for (Object* object : m_listObjects)
		object->LateUpdate();
}

void Scene::Render(HDC _memDC)
{
	for (Object* object : m_listObjects)
		object->Render(_memDC);

	for (std::unique_ptr<Wall>& wall : m_listWalls)
		wall->Render(_memDC);

	for (std::unique_ptr<UI>& ui : m_arrUIs)
		ui->Render(_memDC);
}
