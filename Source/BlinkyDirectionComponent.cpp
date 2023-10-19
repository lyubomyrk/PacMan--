/*
 * Created on Thu Oct 19 2023
 *
 * Copyright (C) 2023 Lyubomyr Kryshtanovskyi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "BlinkyDirectionComponent.hpp"

BlinkyDirectionComponent::BlinkyDirectionComponent(GameBoard *gameBoard, Entity *player)
{
    _gameBoard = gameBoard;
    _player = player;
}

void BlinkyDirectionComponent::Update(Entity *entity) const
{
    const Vector2 currPos = entity->GetPosition();
    const Vector2 currTile = {
        floor(currPos.x / TileUnit),
        floor(currPos.y / TileUnit)};
    const Vector2 currDir = entity->GetDirection();

    // For tie brakers, the last item in this list (highest priority) wins.
    const vector<Vector2> directionPriority = {
        Direction::Up(), Direction::Right(), Direction::Down(), Direction::Left()};
    // Skip these special intersections on up direction.
    const vector<Vector2> specialIntersections = {
        {12, 14}, {15, 14}, {12, 26}, {15, 26}};

    auto target = _player->GetPosition();
    float shortestDistance = LongestDistance;
    Vector2 newDir = currDir;

    for (auto direction : directionPriority)
    {
        // Ghosts can't turn back.
        if (currDir == -direction)
        {
            continue;
        }

        // Check special intersections.
        if (direction == Direction::Up())
        {
            if (find(
                    specialIntersections.begin(), specialIntersections.end(), currTile) != specialIntersections.end())
            {
                continue;
            }
        }

        Vector2 newPos = Vector2Add(currPos, Vector2Scale(direction, TileUnit));

        if (!_gameBoard->IsThereWall(newPos))
        {
            float distance = Vector2Distance(newPos, target);
            if (distance <= shortestDistance)
            {
                newDir = direction;
                shortestDistance = distance;
            }
        }
    }

    entity->SetDirection(newDir);
}
