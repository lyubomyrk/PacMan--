#include "MovementComponent.hpp"

MovementComponent::MovementComponent()
{
}

void MovementComponent::Update(Entity *entity)
{
    Vector2 pos = entity->GetPosition();
    Vector2 dir = entity->GetDirection();
    float speed = entity->GetSpeed();

    Vector2 newPos = Vector2Add(pos, Vector2Scale(dir, speed));
    entity->SetPosition(newPos);
}