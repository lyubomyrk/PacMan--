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

#pragma once

#include "Globals.hpp"
#include "Entity.hpp"
#include "MovingEntity.hpp"
#include "DirectionComponent.hpp"
#include "MovementComponent.hpp"
#include "Timer.hpp"

class Ghost : public MovingEntity
{
    Texture2D _spritesheetBody;
    Texture2D _spritesheetEyes;
    Color _tint;
    int _frameTicks;
    const int _frameRate;
    int _frame;
    const int _maxFrame;

    const Vector2 _startingPosition;
    const Vector2 _startingNormDir;
    const float _regularSpeed = GhostSpeed;
    const float _frigthenedSpeed = GhostSpeed;

    Vector2 _position;
    Vector2 _normDir;
    Vector2 _normDirBuffer;
    DirectionComponent *_scatterDirectionCompoenent;
    DirectionComponent *_chaseDirectionComponent;

    float _speed;
    MovementComponent *_movementComponent;

    Timer _behaviorTimer;
    bool _chasing;

    Timer _frightenedTimer;
    bool _frightened;
    DirectionComponent *_randomDirectionComponent;

public:
    Ghost(
        Color color,
        Vector2 startingPosition,
        Vector2 startingDirection,
        DirectionComponent *scatterDirectionComponent,
        DirectionComponent *chaseDirectionComponent,
        DirectionComponent *randomDirectionComponent,
        MovementComponent *movementCoponent);
    ~Ghost() override;

    void HandleInput();
    void Update();
    void Draw();

    void Start();
    void Stop();
    void Reset();
    void Scatter();
    void Frighten();

    Vector2 GetPosition() const override;
    void SetPosition(Vector2 position) override;
    Vector2 GetDirection() const override;
    void SetDirection(Vector2 direction) override;
    Vector2 GetDirectionBuffer() const override;
    float GetSpeed() const override;
    void SetSpeed(float speed) override;
    Rectangle GetRectangle() const override;

private:
};

Vector2 GhostChooseNextDirection(GameBoard *gameBoard, Vector2 currentPosition, Vector2 currentDir, Vector2 target);