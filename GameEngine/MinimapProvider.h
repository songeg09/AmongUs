#pragma once
#include "pch.h"

class GameObject;
class MinimapProvider abstract
{
public:
    virtual ~MinimapProvider() = default;

    virtual Vector2 GetPlayerPos() const = 0;
    virtual const std::set<GameObject*>& GetGameObjects() const = 0;
};