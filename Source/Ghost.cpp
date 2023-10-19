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

#include "AssetManager.hpp"
#include "Ghost.hpp"

Ghost::Ghost(
    Color color,
    Vector2 position,
    Vector2 direction,
    DirectionComponent *directionComponent,
    MovementComponent *movementCoponent)
    : _frameRate(GhostMovingFps),
      _maxFrame(GhostMovingFrames)
{
    _spritesheetBody = AssetManager::TGhostBody32;
    _spritesheetEyes = AssetManager::TGhostEyes32;
    _tint = color;
    _frameTicks = 0;
    _frame = 0;

    _position = position;
    _normDir = direction;
    _normDirBuffer = _normDir;
    _directionComponent = directionComponent;

    _speed = GhostSpeed;
    _movementComponent = movementCoponent;
}

Ghost::~Ghost()
{
}

void Ghost::HandleInput()
{
}

void Ghost::Update()
{
    _directionComponent->Update(this);
    _movementComponent->Update(this);

    if (_frameTicks++ >= (TargetFps / _frameRate))
    {
        _frameTicks = 0;
        if (_frame++ >= _maxFrame)
        {
            _frame = 0;
        }
    }
}

void Ghost::Draw()
{
    // Draw body.
    DrawTexturePro(
        _spritesheetBody,
        {(float)_frame * SpriteUnit, 0, SpriteUnit, SpriteUnit},
        {_position.x, _position.y, SpriteUnit, SpriteUnit},
        {SpriteUnitOffset, SpriteUnitOffset},
        0.,
        _tint);

    // Draw eyes.
    int eyeFrame;
    if (_normDir == Direction::Right())
    {
        eyeFrame = 0;
    }
    else if (_normDir == Direction::Up())
    {
        eyeFrame = 1;
    }
    else if (_normDir == Direction::Left())
    {
        eyeFrame = 2;
    }
    else if (_normDir == Direction::Down())
    {
        eyeFrame = 3;
    }

    DrawTexturePro(
        _spritesheetEyes,
        {(float)eyeFrame * SpriteUnit, 0, SpriteUnit, SpriteUnit},
        {_position.x, _position.y, SpriteUnit, SpriteUnit},
        {SpriteUnitOffset, SpriteUnitOffset},
        0.,
        WHITE);
}

Vector2 Ghost::GetPosition() const
{
    return _position;
}

void Ghost::SetPosition(Vector2 position)
{
    _position = position;
}

Vector2 Ghost::GetDirection() const
{
    return _normDir;
}

void Ghost::SetDirection(Vector2 direction)
{
    _normDir = direction;
}

Vector2 Ghost::GetDirectionBuffer() const
{
    return _normDirBuffer;
}

float Ghost::GetSpeed() const
{
    return _speed;
}

Rectangle Ghost::GetRectangle() const
{
    return {
        _position.x * TileUnit - TileUnitOffset, _position.y * TileUnit - TileUnitOffset,
        (float)TileUnit, (float)TileUnit};
}