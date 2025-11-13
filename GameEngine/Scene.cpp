#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Core.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Collider.h"

Scene::Scene(std::wstring _strName)
{
	m_strName = _strName;
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
	CollisionManager::GetInstance()->ReleaseCollisionGroup();
}

void Scene::ConfigureRenderSurface(Vector2 _vec2SceneSize, float _fGuardBandPx)
{
	m_vec2SceneSize = _vec2SceneSize;
	m_fGuardBandPx = _fGuardBandPx;
	
	m_vec2BackBufferSize = ConstValue::vec2BaseWindowSize;
	m_vec2BackBufferSize.m_fx += _fGuardBandPx * 2;
	m_vec2BackBufferSize.m_fy += _fGuardBandPx * 2;
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
}
