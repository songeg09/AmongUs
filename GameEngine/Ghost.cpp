#include "pch.h"
#include "Ghost.h"
#include "Collider.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Interactable.h"

Ghost::Ghost()
{
}

Ghost::~Ghost()
{

}

void Ghost::Init(std::vector<Vector2> _wayPoints)
{
	m_arrWayPoints = _wayPoints;
	Character::Init(m_arrWayPoints[rand() % m_arrWayPoints.size()]);

	m_pHearingCollider = CreateCircleCollider(COLLISION_TAG::GHOST_HEARING_SENSOR, true, 1500);
	m_pHearingCollider.lock()->SetBeginCollisionCallBack(std::bind(&Ghost::StartInvestigate, this, std::placeholders::_1));

	m_pSightCollider = CreateCircleCollider(COLLISION_TAG::GHOST_SIGHT_SENSOR, true, 400);
	m_pSightCollider.lock()->SetBeginCollisionCallBack(std::bind(&Ghost::StartChase, this));
	
	m_pChasingCollider = CreateCircleCollider(COLLISION_TAG::GHOST_CHASING_SENSOR, true, 900);
	m_pChasingCollider.lock()->SetBeginCollisionCallBack(
		[this](Collider* _other){
			m_setChaseTargets.insert(_other);
		}
	);
	m_pChasingCollider.lock()->SetEndCollisionCallBack(
		[this](Collider* _other) {
			if(m_setChaseTargets.find(_other) != m_setChaseTargets.end())
				m_setChaseTargets.erase(_other);
		}
	);

	m_pAttackRangeCollider = CreateCircleCollider(COLLISION_TAG::GHOST_ATTACK_RANGE, true, 50);
	m_pAttackRangeCollider.lock()->SetBeginCollisionCallBack(
		[this](Collider* _Other) {
			dynamic_cast<Interactable*>(_Other->GetTarget())->Interact(this); 
		}
	);

	StartPatrol();
}

void Ghost::Update()
{
	switch (m_eState)
	{
	case CHARACTER_STATE::PATROL:
		UpdatePatrol();
		break;
	case CHARACTER_STATE::INVESTIGATE:
		UpdateInvestigate();
		break;
	case CHARACTER_STATE::CHASE:
		UpdateChase();
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

void Ghost::StartPatrol()
{
	Actor::SetMoveSpeed(ConstValue::fGhostDefaultMoveSpeed);
	m_eState = CHARACTER_STATE::PATROL;
	m_vec2TargetPos = m_arrWayPoints[rand() % m_arrWayPoints.size()];
}

void Ghost::StartInvestigate(Collider* _other)
{
	if (m_eState == CHARACTER_STATE::CHASE || m_eState == CHARACTER_STATE::INVESTIGATE)
		return;

	m_vec2TargetPos = _other->GetTarget()->GetPosition();

	Actor::SetMoveSpeed(ConstValue::fGhostInvestigateMoveSpeed);
	m_eState = CHARACTER_STATE::INVESTIGATE;
}

void Ghost::StartChase()
{
	Actor::SetMoveSpeed(ConstValue::fGhostChaseMoveSpeed);
	m_eState = CHARACTER_STATE::CHASE;
}

void Ghost::StartSearch()
{
	if (m_eState != CHARACTER_STATE::INVESTIGATE && m_eState != CHARACTER_STATE::CHASE)
		return;

	Actor::SetMoveSpeed(ConstValue::fGhostDefaultMoveSpeed);
	m_eState = CHARACTER_STATE::SEARCH;
	m_fCurSearchTime = 0.0f;
}

Vector2 Ghost::CreateSearchPoint()
{
	Vector2 newSearchPoint = GetPosition();
	newSearchPoint.m_fx += (std::fmod(rand(), ConstValue::fGhostSearchRange) - (ConstValue::fGhostSearchRange / 2));
	newSearchPoint.m_fy += (std::fmod(rand(), ConstValue::fGhostSearchRange) - (ConstValue::fGhostSearchRange / 2));
	return newSearchPoint;
}

Vector2 Ghost::FindClosestTargetPos()
{
	assert(!m_setChaseTargets.empty());
	
	std::set<Collider*>::iterator it = m_setChaseTargets.begin();

	Vector2 vec2Closest = (*it)->GetTarget()->GetPosition();
	float fDist = Vector2::Distance(GetPosition(), vec2Closest);
	it++;
	
	Vector2 tmpPos;
	float tmpDist;
	while (it != m_setChaseTargets.end())
	{
		tmpPos = (*it)->GetTarget()->GetPosition();
		tmpDist = Vector2::Distance(GetPosition(), tmpPos);
		if (tmpDist < fDist)
		{
			vec2Closest = tmpPos;
			fDist = tmpDist;
		}
		it++;
	}

	return vec2Closest;
}

void Ghost::UpdatePatrol()
{
	if (Vector2::Distance(m_vec2TargetPos, GetPosition()) < ConstValue::fGhostProximityRange)
		m_vec2TargetPos = m_arrWayPoints[rand() % m_arrWayPoints.size()];

	MoveTo(m_vec2TargetPos);
}

void Ghost::UpdateInvestigate()
{
	if (Vector2::Distance(m_vec2TargetPos, GetPosition()) < ConstValue::fGhostProximityRange)
	{
		StartSearch();
		return;
	}

	MoveTo(m_vec2TargetPos);
}

void Ghost::UpdateChase()
{
	if (m_setChaseTargets.empty())
	{
		StartSearch();
		return;
	}

	m_vec2TargetPos = FindClosestTargetPos();
	MoveTo(m_vec2TargetPos);
}

void Ghost::UpdateSearch()
{
	m_fCurSearchTime += TimerManager::GetInstance()->GetfDeltaTime();
	if (m_fCurSearchTime >= ConstValue::fGhostSearchTime)
	{
		StartPatrol();
		return;
	}
		
	if (Vector2::Distance(GetPosition(), m_vec2TargetPos) < ConstValue::fGhostProximityRange)
		m_vec2TargetPos = CreateSearchPoint();

	MoveTo(m_vec2TargetPos);
}

void Ghost::MoveTo(Vector2 _Dest)
{
	Vector2 vec2MoveDirection = _Dest - GetPosition();
	Actor::Move(vec2MoveDirection);
}
