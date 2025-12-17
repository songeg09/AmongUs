#pragma once
#include "IInteractable.h"

class IAttemptable abstract : public IInteractable
{
public:
	~IAttemptable() {}

	virtual void OnSuccess() = 0;
	virtual void OnFail() = 0;
};