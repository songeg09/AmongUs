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
	m_arrWalls.clear();
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

void Scene::CreateWall(Vector2 _vec2Start, Vector2 _vec2End)
{
	std::unique_ptr<Wall> wall = std::make_unique<Wall>();
	wall->Init(_vec2Start, _vec2End);
	m_arrWalls.push_back(std::move(wall));
}

void Scene::RegistObject(std::shared_ptr<Object> _object)
{
	m_arrObjects.push_back(_object);
}

void Scene::UnregistObejct(std::shared_ptr<Object> _object)
{
	std::vector<std::weak_ptr<Object>>::iterator it = std::find(m_arrObjects.begin(), m_arrObjects.end(), _object);
	if (it != m_arrObjects.end())
	{
		*it = m_arrObjects.back();
		m_arrObjects.pop_back();
	}
}

void Scene::RegisterWallDetector(std::shared_ptr<WallDetector> _wallDetector)
{
	m_arrWallDetectors.push_back(_wallDetector);
}

void Scene::UnregisterWallDetector(std::shared_ptr<WallDetector> _wallDetector)
{
	std::vector<std::weak_ptr<WallDetector>>::iterator it = std::find(m_arrWallDetectors.begin(), m_arrWallDetectors.end(),
		[_wallDetector](const std::weak_ptr<WallDetector>& weakPtr)
		{
			// 1. 자물쇠 열어서(lock) 실체 확인
			auto shared = weakPtr.lock();

			// 2. 살아있으면 주소(.get) 비교, 죽었으면(nullptr) false
			if (shared)
				return shared.get() == _wallDetector;

			return false;
		});
	if (it != m_arrWallDetectors.end())
	{
		*it = m_arrWallDetectors.back();
		m_arrWallDetectors.pop_back();
	}
}


void Scene::Update()
{
	for (std::weak_ptr<Object> object: m_arrObjects)
		object.lock()->Update();

	for (std::weak_ptr<WallDetector> detector : m_arrWallDetectors)
		detector.lock()->Update();

	for (std::unique_ptr<Wall>& wall : m_arrWalls)
	{
		for (std::weak_ptr<WallDetector> detector : m_arrWallDetectors)
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
	for (std::weak_ptr<Object> object : m_arrObjects)
		object.lock()->LateUpdate();
}

void Scene::Render(HDC _memDC)
{
	for (std::weak_ptr<Object> object : m_arrObjects)
		object.lock()->Render(_memDC);

	for (std::unique_ptr<Wall>& wall : m_arrWalls)
		wall->Render(_memDC);

	for (std::unique_ptr<UI>& ui : m_arrUIs)
		ui->Render(_memDC);
}
