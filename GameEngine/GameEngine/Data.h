#pragma once
#include "GameResource.h"
class Data : public GameResource
{
public:
	virtual void Load(std::wifstream& _loadFile) = 0;
};

