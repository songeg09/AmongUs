#pragma once
#include "pch.h"

class Attemptable;
class MinimapProvider abstract
{
public:
    virtual ~MinimapProvider() = default;

    virtual Vector2 GetPlayerPos() const = 0;
    virtual const std::set<Attemptable*>& GetGameObjects() const = 0;
};