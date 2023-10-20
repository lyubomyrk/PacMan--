/*
 * Created on Fri Oct 20 2023
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

#include "InkyDirectionComponent.hpp"
#include "Ghost.hpp"

const int PlayerLead = 2;
const int VectorScale = 2;

InkyDirectionComponent::InkyDirectionComponent(GameBoard *gameBoard, Entity *player, Entity *blinky)
{
    _gameBoard = gameBoard;
    _player = player;
    _blinky = blinky;
}

void InkyDirectionComponent::Update(Entity *entity) const
{
    Vector2 currPos = entity->GetPosition();
    Vector2 currDir = entity->GetDirection();

    Vector2 playerPos = _player->GetPosition();
    Vector2 playerDir = _player->GetDirection();
    Vector2 playerOffset = Vector2Add(playerPos, Vector2Scale(playerDir, PlayerLead * TileUnit));

    Vector2 blinkyPos = _blinky->GetPosition();
    Vector2 blinkyToOffset = Vector2Subtract(playerOffset, blinkyPos);

    Vector2 blinkyToOffsetNorm = Vector2Normalize(blinkyToOffset);
    float blinkyToOffsetLength = Vector2Length(blinkyToOffset);

    Vector2 target = Vector2Add(blinkyPos, Vector2Scale(blinkyToOffsetNorm, VectorScale * blinkyToOffsetLength));

    

    Vector2 newDir = GhostChooseNextDirection(_gameBoard, currPos, currDir, target);

    entity->SetDirection(newDir);
}
