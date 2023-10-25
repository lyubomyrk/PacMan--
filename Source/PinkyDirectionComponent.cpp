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

#include "PinkyDirectionComponent.hpp"
#include "Ghost.hpp"

const int PlayerLead = 4;

PinkyDirectionComponent::PinkyDirectionComponent(GameBoard *gameBoard, MovingEntity *player)
{
    _gameBoard = gameBoard;
    _player = player;
}

void PinkyDirectionComponent::Update(MovingEntity *entity) const
{
    Vector2 currPos = entity->GetPosition();
    Vector2 currDir = entity->GetDirection();
    Vector2 playerPos = _player->GetPosition();
    Vector2 playerDir = _player->GetDirection();

    Vector2 target = Vector2Add(playerPos, Vector2Scale(playerDir, PlayerLead * TileUnit));

    Vector2 newDir = GhostChooseNextDirection(_gameBoard, currPos, currDir, target);

    entity->SetDirection(newDir);
}