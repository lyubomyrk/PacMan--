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
#include "Ghost.hpp"

BlinkyDirectionComponent::BlinkyDirectionComponent(GameBoard *gameBoard, Entity *player)
{
    _gameBoard = gameBoard;
    _player = player;
}

void BlinkyDirectionComponent::Update(Entity *entity) const
{
    const Vector2 currPos = entity->GetPosition();
    const Vector2 currDir = entity->GetDirection();
    const Vector2 target = _player->GetPosition();

    Vector2 newDir = GhostChooseNextDirection(_gameBoard, currPos, currDir, target);

    entity->SetDirection(newDir);
}
