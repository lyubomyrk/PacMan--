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
    Vector2 startingPosition,
    Vector2 startingDirection,
    DirectionComponent *scatterDirectionComponent,
    DirectionComponent *chaseDirectionComponent,
    DirectionComponent *randomDirectionComponent,
    MovementComponent *movementCoponent)
    : _startingPosition(startingPosition),
      _startingNormDir(startingDirection),
      _frameRate(GhostMovingFps),
      _maxFrame(GhostMovingFrames)
{
    _spritesheetBody = AssetManager::TGhostBody32;
    _spritesheetEyes = AssetManager::TGhostEyes32;
    _tint = color;
    _frameTicks = 0;
    _frame = 0;

    _position = _startingPosition;
    _normDir = _startingNormDir;
    _normDirBuffer = _normDir;
    _scatterDirectionCompoenent = scatterDirectionComponent;
    _chaseDirectionComponent = chaseDirectionComponent;

    _speed = 0.;
    _movementComponent = movementCoponent;

    _behaviorTimer.Start(GhostScatterTime);
    _chasing = false;

    _frightened = false;
    _randomDirectionComponent = randomDirectionComponent;
}

Ghost::~Ghost()
{
}

void Ghost::HandleInput()
{
    if (_frightened)
    {
        _randomDirectionComponent->Update(this);
    }
    else if (_chasing)
    {
        _chaseDirectionComponent->Update(this);
    }
    else
    {
        _scatterDirectionCompoenent->Update(this);
    }
}

void Ghost::Update()
{
    _movementComponent->Update(this);

    if (_frameTicks++ >= (TargetFps / _frameRate))
    {
        _frameTicks = 0;
        if (_frame++ >= _maxFrame)
        {
            _frame = 0;
        }
    }

    if (_speed != 0. && _frightened)
        _frightenedTimer.Update();

    if (_frightened && _frightenedTimer.IsFinished())
    {
        _frightened = false;
        _speed = GhostSpeed;
    }

    if (_speed != 0. && !_frightened)
        _behaviorTimer.Update();

    if (_behaviorTimer.IsFinished())
    {
        if (_chasing)
        {
            _behaviorTimer.Start(GhostScatterTime);
            _chasing = false;
        }
        else
        {
            _behaviorTimer.Start(GhostChaseTime);
            _chasing = true;
        }

        _normDir = -_normDir;
    }
}

void Ghost::Draw()
{
    Color bodyColor = _tint;

    if (_frightened)
    {
        bodyColor = BLUE;
    }

    // Draw body.
    DrawTexturePro(
        _spritesheetBody,
        {(float)_frame * SpriteUnit, 0, SpriteUnit, SpriteUnit},
        {_position.x, _position.y, SpriteUnit, SpriteUnit},
        {SpriteUnitOffset, SpriteUnitOffset},
        0.,
        bodyColor);

    // Draw eyes.
    int eyeFrame;
    if (_frightened)
    {
        eyeFrame = 4;
    }
    else if (_normDir == Direction::Right())
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

void Ghost::Start()
{
    _speed = GhostSpeed;
}

void Ghost::Stop()
{
    _speed = 0.;
}

void Ghost::Reset()
{
    _position = _startingPosition;
    _normDir = _startingNormDir;
    _normDirBuffer = _normDir;
    _speed = 0.;

    _chasing = false;
    _behaviorTimer.Start(GhostScatterTime);
}

void Ghost::Scatter()
{
}

void Ghost::Frighten()
{
    _frightened = true;
    _frightenedTimer.Start(EnergizerTime);
    _speed = GhostSpeed / 2;
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

void Ghost::SetSpeed(float speed)
{
    _speed = speed;
}

Rectangle Ghost::GetRectangle() const
{
    return {
        _position.x * TileUnit - TileUnitOffset, _position.y * TileUnit - TileUnitOffset,
        (float)TileUnit, (float)TileUnit};
}

Vector2 GhostChooseNextDirection(GameBoard *gameBoard, Vector2 currentPosition, Vector2 currentDir, Vector2 target)
{
    const Vector2 currTile = {
        floor(currentPosition.x / TileUnit),
        floor(currentPosition.y / TileUnit)};

    // For tie brakers, the last item in this list (highest priority) wins.
    const vector<Vector2> directionPriority = {
        Direction::Up(), Direction::Right(), Direction::Down(), Direction::Left()};
    // Skip these special intersections on up direction.
    const vector<Vector2> specialIntersections = {
        {12, 14}, {15, 14}, {12, 26}, {15, 26}};

    float shortestDistance = LongestDistance;
    Vector2 newDir = currentDir;

    for (auto direction : directionPriority)
    {
        // Ghosts can't turn back.
        if (direction == -currentDir)
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

        Vector2 newPos = Vector2Add(currentPosition, Vector2Scale(direction, TileUnit));

        if (!gameBoard->IsThereWall(newPos))
        {
            float distance = Vector2Distance(newPos, target);
            if (distance <= shortestDistance)
            {
                newDir = direction;
                shortestDistance = distance;
            }
        }
    }

    return newDir;
}