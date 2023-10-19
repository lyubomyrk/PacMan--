#pragma once

#include "Globals.hpp"

class Entity
{
public:
    virtual ~Entity() {}
    virtual Vector2 GetPosition() const = 0;
    virtual void SetPosition(Vector2 position) = 0;
    virtual Vector2 GetDirection() const = 0;
    virtual float GetSpeed() const = 0;
    virtual Rectangle GetRectangle() const = 0;
};