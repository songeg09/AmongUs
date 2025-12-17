#pragma once
#include "pch.h"

class IAttemptable;
class IMinimapProvider abstract
{
public:
    virtual ~IMinimapProvider() = default;

    virtual Vector2 GetPlayerPos() const = 0;
    virtual const std::set<IAttemptable*>& GetGameObjects() const = 0;
};