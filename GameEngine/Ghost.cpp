#include "pch.h"
#include "Ghost.h"
#include "CircleZone.h"
#include "Collider.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Interactable.h"

Ghost::Ghost()
{
	m_pHearingCollider = nullptr;
	m_pSightCollider = nullptr;
	m_pAttackRangeCollider = nullptr;
}

Ghost::~Ghost()
{

}

void Ghost::Init(std::vector<Vector2> _wayPoints)
{
	m_arrWayPoints = _wayPoints;
	m_iCurWayPoint = rand() % m_arrWayPoints.size();
	Character::Init(_wayPoints[m_iCurWayPoint]);

	m_pHearingCollider = CreateCircleCollider(COLLISION_TAG::GHOST_HEARING_SENSOR, true, 3000);
	m_pHearingCollider->SetBeginCollisionCallBack(std::bind(&Ghost::ChangeState, this, CHARACTER_STATE::INVESTIGATE));
	m_pHearingCollider->SetOnCollisionCallBack(
		[this](Collider* _Other) { MoveTo(_Other->GetPosition()); }
	);
	m_pHearingCollider->SetEndCollisionCallBack(std::bind(&Ghost::ChangeState, this, CHARACTER_STATE::SEARCH));

	m_pSightCollider = CreateCircleCollider(COLLISION_TAG::GHOST_SIGHT_SENSOR, true, 400);
	m_pSightCollider->SetBeginCollisionCallBack(std::bind(&Ghost::ChangeState, this, CHARACTER_STATE::CHASE));
	
	m_pChasingCollider = CreateCircleCollider(COLLISION_TAG::GHOST_CHASING_SENSOR, true, 900);
	m_pChasingCollider->SetOnCollisionCallBack(
		[this](Collider* _Other) {MoveTo(_Other->GetPosition()); }
	);
	m_pChasingCollider->SetEndCollisionCallBack(std::bind(&Ghost::StartSearch, this));
	m_pChasingCollider->SetEnable(false);

	m_pAttackRangeCollider = CreateCircleCollider(COLLISION_TAG::GHOST_ATTACK_RANGE, true, 50);
	m_pAttackRangeCollider->SetBeginCollisionCallBack(
		[this](Collider* _Other) {
			dynamic_cast<Interactable*>(_Other->GetTarget())->Interact(this); 
		}
	);

	m_eState = CHARACTER_STATE::PATROL;
}

void Ghost::Update()
{
	switch (m_eState)
	{
	case CHARACTER_STATE::PATROL:
		UpdatePatrol();
		break;
	case CHARACTER_STATE::SEARCH:
		UpdateSearch();
		break;
	}
	Character::Update();
}

void Ghost::InitAnimation()
{
	AnimationData Idle(TEXTURE_TYPE::CHARACTER, Vector2(0, 10), Vector2(128, 128), 0, 16, ANIMATION_TYPE::LOOP, 2.0f, ANCHOR::CENTER);
	
	Actor::ResizeAnimation(ANIMATION::END);
	Actor::InitAnimation(ANIMATION::IDLE, Idle);
	Actor::SetAnimation(ANIMATION::IDLE);
}

void Ghost::ChangeState(CHARACTER_STATE _eState)
{
	switch (_eState)
	{
	case CHARACTER_STATE::PATROL:
		m_eState = _eState;
		break;
	case CHARACTER_STATE::INVESTIGATE:
		StartInvestigate();
		break;
	case CHARACTER_STATE::CHASE:
		StartChase();
		break;
	case CHARACTER_STATE::SEARCH:
		StartSearch();
		break;
	}
}

void Ghost::StartInvestigate()
{
	Actor::SetMoveSpeed(200.0f);
	m_eState = CHARACTER_STATE::INVESTIGATE;
}

void Ghost::StartChase()
{
	m_pHearingCollider->SetEnable(false);
	m_pSightCollider->SetEnable(false);
	m_pChasingCollider->SetEnable(true);
	Actor::SetMoveSpeed(250.0f);
	m_eState = CHARACTER_STATE::CHASE;
}

void Ghost::StopChase()
{
	m_pHearingCollider->SetEnable(true);
	m_pSightCollider->SetEnable(true);
	m_pChasingCollider->SetEnable(false);
	Actor::SetMoveSpeed(100.0f);
}

void Ghost::StartSearch()
{
	StopChase();
	m_fCurSearchTime = 0;
	m_vec2SearchPoint = CreateSearchPoint();
	m_eState = CHARACTER_STATE::SEARCH;
}

Vector2 Ghost::CreateSearchPoint()
{
	Vector2 newSearchPoint = GetPosition();
	newSearchPoint.m_fx += (std::fmod(rand(), ConstValue::fGhostSearchRange) - (ConstValue::fGhostSearchRange / 2));
	newSearchPoint.m_fy += (std::fmod(rand(), ConstValue::fGhostSearchRange) - (ConstValue::fGhostSearchRange / 2));
	return newSearchPoint;
}

void Ghost::UpdatePatrol()
{
	if (Vector2::Distance(m_arrWayPoints[m_iCurWayPoint], GetPosition()) < ConstValue::fGhostProximityRange)
		m_iCurWayPoint = rand() % m_arrWayPoints.size();

	MoveTo(m_arrWayPoints[m_iCurWayPoint]);
}

void Ghost::UpdateSearch()
{
	m_fCurSearchTime += TimerManager::GetInstance()->GetfDeltaTime();
	if (m_fCurSearchTime >= ConstValue::fGhostSearchTime)
		m_eState = CHARACTER_STATE::PATROL;

	if (Vector2::Distance(GetPosition(), m_vec2SearchPoint) < ConstValue::fGhostProximityRange)
		m_vec2SearchPoint = CreateSearchPoint();

	MoveTo(m_vec2SearchPoint);
}

void Ghost::MoveTo(Vector2 _Dest)
{
	Vector2 vec2MoveDirection = _Dest - GetPosition();
	Actor::Move(vec2MoveDirection);
}
