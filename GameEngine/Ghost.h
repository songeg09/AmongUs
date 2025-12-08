#pragma once
#include "Character.h"

class Collider;
class Ghost: public Character
{
public:
	enum CHARACTER_STATE
	{
		PATROL,
		INVESTIGATE,
		CHASE,
		SEARCH
	};

	enum ANIMATION
	{
		IDLE,
		END,
	};

private:
	std::shared_ptr<Collider>			m_pHearingCollider;
	std::shared_ptr<Collider>			m_pSightCollider;
	std::shared_ptr<Collider>			m_pChasingCollider;
	std::shared_ptr<Collider>			m_pAttackRangeCollider;

	std::set<Collider*>					m_setChaseTargets;

	CHARACTER_STATE						m_eState;

	std::vector<Vector2>				m_arrWayPoints;

	float								m_fCurSearchTime;
	Vector2								m_vec2TargetPos;

public:
	Ghost();
	~Ghost();

	void Init(std::vector<Vector2> _wayPoints);
	void Update() override;

	void InitAnimation() override;

private:
	void StartPatrol();
	void StartInvestigate(Collider* _other);
	void StartChase();
	void StartSearch();
	Vector2 CreateSearchPoint();
	Vector2 FindClosestTargetPos();

	void UpdatePatrol();
	void UpdateInvestigate();
	void UpdateChase();
	void UpdateSearch();

	void MoveTo(Vector2 _Dest);
};

