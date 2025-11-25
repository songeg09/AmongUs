#pragma once
#include "Character.h"

class Collider;
class RectZone;
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
	Collider*			m_pHearingCollider;
	Collider*			m_pSightCollider;
	Collider*			m_pChasingCollider;
	Collider*			m_pAttackRangeCollider;

	CHARACTER_STATE			m_eState;

	std::vector<Vector2>	m_arrWayPoints;
	int						m_iCurWayPoint;

	float					m_fCurSearchTime;
	Vector2					m_vec2SearchPoint;

public:
	Ghost();
	~Ghost();

	void Init(Vector2 _vec2Position, std::vector<Vector2> _wayPoints);
	void Update() override;

	void InitAnimation() override;

	void ChangeState(CHARACTER_STATE _eState);

private:
	void StartInvestigate();
	void StartChase();
	void StopChase();
	void StartSearch();
	Vector2 CreateSearchPoint();

	void UpdatePatrol();
	void UpdateSearch();

	void MoveTo(Vector2 _Dest);
};

