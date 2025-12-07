#include "pch.h"
#include "Object.h"
#include "Texture.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include "WallDetector.h"

Object::Object()
{
	m_vec2Position = {};
	m_vec2Scale = {};

	SceneManager::GetInstance()->GetCurScene()->RegistObject(this);
}

Object::~Object()
{
	SceneManager::GetInstance()->GetCurScene()->UnregistObejct(this);
}

void Object::LateUpdate()
{
	for (std::weak_ptr<Collider> collider : m_pColliderList)
		collider.lock()->FinalUpdate();
}

void Object::Render(HDC _memDC)
{
	ColliderRender(_memDC);
}

void Object::Init(Vector2 _vec2Position)
{
	m_vec2MoveVec = { 0,0 };
	SetPosition(_vec2Position);
}

std::shared_ptr<Collider>Object::CreateRectCollider(COLLISION_TAG _eTag, bool _eEnabled, Vector2 _vecSize, Vector2 _vecOffset)
{
	std::shared_ptr<RectCollider> collider = std::make_shared<RectCollider>(_eTag);
	collider->SetTarget(shared_from_this());
	collider->Init(_eEnabled, _vecSize, _vecOffset);
	m_pColliderList.push_back(collider);

	return collider;
}

std::shared_ptr<Collider> Object::CreateCircleCollider(COLLISION_TAG _eTag, bool _eEnabled, float _fRadius, Vector2 _vecOffset)
{
	std::shared_ptr<CircleCollider> collider = std::make_shared<CircleCollider>(_eTag);
	collider->SetTarget(shared_from_this());
	collider->Init(_eEnabled, _fRadius, _vecOffset);
	m_pColliderList.push_back(collider);

	return collider;
}

std::shared_ptr<WallDetector> Object::CreateWallDetector(Vector2 _vec2Offset, float _fRadius)
{
	std::shared_ptr<WallDetector> wallDetector = std::make_shared<WallDetector>();
	wallDetector->Init(shared_from_this(), Vector2(0, 40), 20.0f);
	return wallDetector;
}


void Object::ColliderRender(HDC _memDC)
{
	for (std::weak_ptr<Collider> collider : m_pColliderList)
		collider.lock()->Render(_memDC);
}

