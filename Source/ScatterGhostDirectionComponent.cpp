#include "ScatterGhostDirectionComponent.hpp"
#include "Ghost.hpp"

ScatterGhostDirectionComponent::ScatterGhostDirectionComponent(GameBoard *gameBoard, Vector2 scatterTile)
{
    _gameBoard = gameBoard;
    _scatterTile = scatterTile;
}

void ScatterGhostDirectionComponent::Update(MovingEntity *entity) const
{
    const Vector2 currPos = entity->GetPosition();
    const Vector2 currDir = entity->GetDirection();
    const Vector2 target = _scatterTile;

    Vector2 newDir = GhostChooseNextDirection(_gameBoard, currPos, currDir, target);

    entity->SetDirection(newDir);
}