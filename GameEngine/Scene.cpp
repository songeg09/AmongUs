#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Core.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "UI.h"

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

	for (Object* object : m_arrObjects)
	{
		delete object;
	}
	m_arrObjects.clear();

	for (UI* ui : m_arrUIs)
	{
		delete ui;
	}
	m_arrUIs.clear();

	for (std::vector<Collider*>& colliders : m_arrColliders)
		colliders.clear();

	CollisionManager::GetInstance()->ReleaseCollisionGroup();
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
	m_arrObjects.push_back(_object);
}

void Scene::AddCollider(Collider* _collider, COLLISION_TAG _eTag)
{
	m_arrColliders[static_cast<int>(_eTag)].push_back(_collider);
}

void Scene::Update()
{
	for (int i = 0; i < m_arrObjects.size(); i++)
		m_arrObjects[i]->Update();

	for (UI* ui : m_arrUIs)
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
	for (int i = 0; i < m_arrObjects.size(); i++)
		m_arrObjects[i]->LateUpdate();
}

void Scene::Render(HDC _memDC)
{
	for (Object* object : m_arrObjects)
		object->Render(_memDC);

	for (UI* ui : m_arrUIs)
		ui->Render(_memDC);
}
