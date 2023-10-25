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

#include "PlayerDirectionComponent.hpp"

PlayerDirectionComponent::PlayerDirectionComponent(GameBoard *gameBoard)
{
    _gameBoard = gameBoard;
}

void PlayerDirectionComponent::Update(MovingEntity *entity) const
{
    Vector2 position = entity->GetPosition();
    Vector2 dirBuffer = entity->GetDirectionBuffer();

    Vector2 posBuffer = Vector2Add(position, Vector2Scale(dirBuffer, TileUnit));

    if (!_gameBoard->IsThereWall(posBuffer))
    {
        entity->SetDirection(dirBuffer);
    }
}