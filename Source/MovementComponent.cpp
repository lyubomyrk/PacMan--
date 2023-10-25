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

#include "MovementComponent.hpp"

MovementComponent::MovementComponent(GameBoard *gameBoard)
{
    _gameBoard = gameBoard;
}

void MovementComponent::Update(MovingEntity *entity)
{
    Vector2 pos = entity->GetPosition();
    Vector2 dir = entity->GetDirection();
    float speed = entity->GetSpeed();

    Vector2 newPos = Vector2Add(pos, Vector2Scale(dir, speed));

    if (newPos.x <= 0)
    {
        newPos.x = WindowWidth - TileUnitOffset;
    }
    if (newPos.x >= WindowWidth)
    {
        newPos.x = TileUnitOffset;
    }

    if (!_gameBoard->IsThereWall(newPos))
    {
        entity->SetPosition(newPos);
    }
}