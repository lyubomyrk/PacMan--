#include "RandomDirectionComponent.hpp"
#include "Globals.hpp"
#include "Ghost.hpp"
#include "raylib.h"

RandomDirectionComponent::RandomDirectionComponent(GameBoard *gameBoard)
{
    _gameBoard = gameBoard;
}

void RandomDirectionComponent::Update(MovingEntity *entity) const
{
    Vector2 currPos = entity->GetPosition();
    const Vector2 currDir = entity->GetDirection();
    Vector2 newDir;

    int maxAttempts = 5;
    int attempts = 0;
    do
    {
        Vector2 directions[] = {Direction::Up(), Direction::Down(), Direction::Left(), Direction::Right()};
        newDir = directions[rand() % 4];
        attempts++;
    } while (attempts < maxAttempts && (newDir == -currDir || _gameBoard->IsThereWall(Vector2Add(currPos, Vector2Scale(newDir, TileUnit)))));

    if (attempts < maxAttempts)
        entity->SetDirection(newDir);
}
