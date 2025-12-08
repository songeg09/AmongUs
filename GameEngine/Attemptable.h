#pragma once
#include "Interactable.h"

class Attemptable abstract : public Interactable
{
public:
	~Attemptable() {}

	virtual void OnSuccess() = 0;
	virtual void OnFail() = 0;
};