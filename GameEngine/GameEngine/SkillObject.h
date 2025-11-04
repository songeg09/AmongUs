#pragma once
#include "Object.h"
class SkillObject abstract : public Object
{
protected:
	Object* m_pTarget;
	bool m_bEnable;

public:
	SkillObject();
	virtual ~SkillObject();
	void Init(Object* _pTarget);
	// Object을(를) 통해 상속됨
	virtual void Update() override;
	
	bool GetEnbale() { return m_bEnable; }
	virtual void SetEnable(bool _bEnable);
};

