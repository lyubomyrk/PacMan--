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

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "raylib.h"
#include "raymath.h"

using namespace std;

constexpr bool DEBUG = false;

const int WindowWidth = 672;
const int WindowHeight = 888;
const string WindowTitle = "PacMan++";

const int TargetFps = 60;

enum class Tile
{
    Empty = ' ',
    Wall = '#',
    Pellet = '*',
    Energizer = '^',
    Door = '=',
    Fruit = 'F',
    Bell = 'B',
    Key = 'K',
};

const int TileUnit = 24;
const int TileUnitOffset = TileUnit / 2;
const int SpriteUnit = 32;
const int SpriteUnitOffset = SpriteUnit / 2;

const int BoardRows = 36;
const int BoardColumns = 28;
const float LongestDistance = sqrt(pow(BoardColumns * TileUnit, 2) + pow(BoardRows * TileUnit, 2));
// clang-format off
const char Board[BoardRows][BoardColumns] = {
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
  {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
  {'#','*','*','*','*','*','*','*','*','*','*','*','*','#','#','*','*','*','*','*','*','*','*','*','*','*','*','#',},
  {'#','*','#','#','#','#','*','#','#','#','#','#','*','#','#','*','#','#','#','#','#','*','#','#','#','#','*','#',},
  {'#','^','#','#','#','#','*','#','#','#','#','#','*','#','#','*','#','#','#','#','#','*','#','#','#','#','^','#',},
  {'#','*','#','#','#','#','*','#','#','#','#','#','*','#','#','*','#','#','#','#','#','*','#','#','#','#','*','#',},
  {'#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#',},
  {'#','*','#','#','#','#','*','#','#','*','#','#','#','#','#','#','#','#','*','#','#','*','#','#','#','#','*','#',},
  {'#','*','#','#','#','#','*','#','#','*','#','#','#','#','#','#','#','#','*','#','#','*','#','#','#','#','*','#',},
  {'#','*','*','*','*','*','*','#','#','*','*','*','*','#','#','*','*','*','*','#','#','*','*','*','*','*','*','#',},
  {'#','#','#','#','#','#','*','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#','#','#','#',' ','#','#',' ','#','#','#','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#',' ','#','#','#','=','=','#','#','#',' ','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#','#','*','#','#','#','#','#','#',},
  {' ',' ',' ',' ',' ',' ','*','*','*',' ','#',' ',' ',' ',' ',' ',' ','#',' ','*','*','*',' ',' ',' ',' ',' ',' ',},
  {'#','#','#','#','#','#','*','#','#',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','*','#','#','#','#','#','#',},
  {'#','#','#','#','#','#','*','#','#',' ','#','#','#','#','#','#','#','#',' ','#','#','*','#','#','#','#','#','#',},
  {'#','*','*','*','*','*','*','*','*','*','*','*','*','#','#','*','*','*','*','*','*','*','*','*','*','*','*','#',},
  {'#','*','#','#','#','#','*','#','#','#','#','#','*','#','#','*','#','#','#','#','#','*','#','#','#','#','*','#',},
  {'#','*','#','#','#','#','*','#','#','#','#','#','*','#','#','*','#','#','#','#','#','*','#','#','#','#','*','#',},
  {'#','^','*','*','#','#','*','*','*','*','*','*','*',' ',' ','*','*','*','*','*','*','*','#','#','*','*','^','#',},
  {'#','#','#','*','#','#','*','#','#','*','#','#','#','#','#','#','#','#','*','#','#','*','#','#','*','#','#','#',},
  {'#','#','#','*','#','#','*','#','#','*','#','#','#','#','#','#','#','#','*','#','#','*','#','#','*','#','#','#',},
  {'#','*','*','*','*','*','*','#','#','*','*','*','*','#','#','*','*','*','*','#','#','*','*','*','*','*','*','#',},
  {'#','*','#','#','#','#','#','#','#','#','#','#','*','#','#','*','#','#','#','#','#','#','#','#','#','#','*','#',},
  {'#','*','#','#','#','#','#','#','#','#','#','#','*','#','#','*','#','#','#','#','#','#','#','#','#','#','*','#',},
  {'#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#',},
  {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',},
};
// clang-format on

const Vector2 PacmanStartingPosition = {
    14 * TileUnit, 26 * TileUnit + TileUnitOffset};
const Vector2 RedGhostStartingPosition = {
    14 * TileUnit, 14 * TileUnit + TileUnitOffset};
const Vector2 RedGhostScatterTargetPosition = {
    25 * TileUnit + TileUnitOffset, 0};
const Vector2 PinkGhostStartingPosition = {
    14 * TileUnit, 17 * TileUnit + TileUnitOffset};
const Vector2 PinkGhostScatterTargetPosition = {
    2 * TileUnit + TileUnitOffset, 0};
const Vector2 BlueGhostStartingPosition = {
    11.5 * TileUnit + TileUnitOffset, 17 * TileUnit + TileUnitOffset};
const Vector2 BlueGhostScatterTargetPosition = {
    27 * TileUnit + TileUnitOffset, 35 * TileUnit + TileUnitOffset};
const Vector2 OrangeGhostStartingPosition = {
    15.5 * TileUnit + TileUnitOffset, 17 * TileUnit + TileUnitOffset};
const Vector2 OrangeGhostScatterTargetPosition = {
    0, 35 * TileUnit + TileUnitOffset};

const int PacmanSpeed = 2;
const int PacmanMovingFrames = 3;
const int PacmanMovingFps = 15;

const int GhostSpeed = 2;
const int GhostEatenSpeed = 4;
const int GhostMovingFrames = 6;
const int GhostMovingFps = 15;

const float IntroTime = 5.0;
const float EnergizerTime = 5.0;

class Direction
{
public:
    Direction() = delete;

    static Vector2 Up() { return {0., -1.}; }
    static Vector2 Down() { return {0., 1.}; }
    static Vector2 Right() { return {1., 0.}; }
    static Vector2 Left() { return {-1., 0.}; }
};
inline bool operator==(Vector2 left, Vector2 right)
{
    return left.x == right.x && left.y == right.y;
}
inline bool operator!=(Vector2 left, Vector2 right)
{
    return !(left == right);
}
inline Vector2 operator-(Vector2 right)
{
    return {-right.x, -right.y};
}

inline void PlaySoundIfNotPlaying(Sound sound)
{
    if (!IsSoundPlaying(sound))
    {
        PlaySound(sound);
    }
}

inline void PlaySoundOnConditional(Sound sound, bool condition)
{
    if (condition)
    {
        PlaySoundIfNotPlaying(sound);
    }
    else
    {
        StopSound(sound);
    }
}