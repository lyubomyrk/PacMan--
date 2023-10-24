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

class GameBoard
{
    vector<vector<Tile>> _gameBoard;

    int _pellets;

    vector<Rectangle> _debugCollisionRecs;

public:
    GameBoard();
    ~GameBoard();
    void Draw();

    void Reset();
    bool IsThereWall(Vector2 position);
    bool IsThere(Vector2 position, Tile tile);
    void Remove(Vector2 position, Tile type);
    void AddDebugRec(Vector2 position);
    void DrawDebugRecs();

private:
};