/*
 * Created on Tue Oct 17 2023
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

#pragma once

#include "Globals.hpp"
#include "Entity.hpp"
#include "MovementComponent.hpp"

class PacMan : public Entity
{
    Texture2D _spritesheet;
    Color _tint;
    int _frameTicks;
    const int _frameRate;
    int _frame;
    const int _maxFrame;

    Vector2 _position;
    Vector2 _normDir;
    Vector2 _normDirBuffer;

    float _speed;
    MovementComponent *_movementComponent;

public:
    PacMan(MovementComponent *movementComponent);
    ~PacMan() override;

    void HandleInput();
    void Update();
    void Draw();

    Vector2 GetPosition() const override;
    void SetPosition(Vector2 position) override;
    Vector2 GetDirection() const override;
    float GetSpeed() const override;
    Rectangle GetRectangle() const override;

private:
};