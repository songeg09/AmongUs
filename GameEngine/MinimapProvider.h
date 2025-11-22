#pragma once
#include "pch.h"

class Interactable;
class MinimapProvider abstract
{
public:
    virtual ~MinimapProvider() = default;

    virtual Vector2 GetPlayerPos() const = 0;
    virtual const std::set<Interactable*>& GetGameObjects() const = 0;
};