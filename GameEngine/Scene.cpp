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

void Scene::SetSceneSize(int _iWidth, int _iHeight)
{
	m_vec2SceneSize = { static_cast<float>(_iWidth),static_cast<float>(_iHeight) };
}

void Scene::SetViewPortSize(Vector2 _Size)
{
	m_vec2ViewPortSize = _Size;

	Vector2 vec2ScreenStartPosition = { GetSystemMetrics(SM_CXSCREEN) / 2.0f,GetSystemMetrics(SM_CYSCREEN) / 2.0f };
	Vector2 m_vec2WindowStartPosition = { vec2ScreenStartPosition.m_fx - (m_vec2ViewPortSize.m_fx / 2.0f),
											  vec2ScreenStartPosition.m_fy - (m_vec2ViewPortSize.m_fy / 2.0f) };

	SetWindowPos(Core::GetInstance()->GethWnd(), nullptr, m_vec2WindowStartPosition.m_fx, m_vec2WindowStartPosition.m_fy,
		m_vec2ViewPortSize.m_fx + 16, m_vec2ViewPortSize.m_fy + 39, SWP_SHOWWINDOW);

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
