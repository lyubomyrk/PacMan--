#include "MovementComponent.hpp"

MovementComponent::MovementComponent(GameBoard *gameBoard)
{
    _gameBoard = gameBoard;
}

void MovementComponent::Update(Entity *entity)
{
    Vector2 pos = entity->GetPosition();
    Vector2 dir = entity->GetDirection();
    float speed = entity->GetSpeed();

    Vector2 newPos = Vector2Add(pos, Vector2Scale(dir, speed));

    if (!_gameBoard->IsThereWall(newPos))
    {
        entity->SetPosition(newPos);
    }
}