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
#include "GameBoard.hpp"

GameBoard::GameBoard()
{
}

void GameBoard::Reset()
{
    _gameBoard.clear();

    for (int i = 0; i < BoardRows; i++)
    {

        _gameBoard.push_back(vector<Tile>());
        for (int j = 0; j < BoardColumns; j++)
        {
            _gameBoard[i].push_back((Tile)Board[i][j]);
        }
    }
}

bool GameBoard::IsThereWall(Vector2 position)
{
    if (
        position.x < 0 ||
        position.x > BoardColumns * TileUnit ||
        position.y < 0 ||
        position.y > BoardRows * TileUnit)
    {

        throw new invalid_argument("position is out of bounds.");
    }
    Rectangle rec = {
        position.x - TileUnitOffset, position.y - TileUnitOffset,
        (float)TileUnit, (float)TileUnit};
    int boundingTop = rec.y / TileUnit;
    int boundingBottom = boundingTop + (rec.height / TileUnit);
    int boundingLeft = rec.x / TileUnit;
    int boundingRight = boundingLeft + (rec.width / TileUnit);

    if (boundingTop < 0)
        boundingTop = 0;
    if (boundingBottom >= BoardRows)
        boundingBottom = BoardRows - 1;
    if (boundingLeft < 0)
        boundingLeft = 0;
    if (boundingRight >= BoardColumns)
        boundingRight = BoardColumns - 1;

    // if constexpr (DEBUG)
    // {
    //     DebugCollisionRecs.push_back(
    //         {(float)boundingLeft * TileUnit, (float)boundingTop * TileUnit,
    //          (float)(boundingRight - boundingLeft) * TileUnit, (float)(boundingBottom - boundingTop) * TileUnit});
    // }

    for (int y = boundingTop; y <= boundingBottom; y++)
    {
        for (int x = boundingLeft; x <= boundingRight; x++)
        {
            if (_gameBoard[y][x] == Tile::Wall)
            {
                Rectangle wallRec = {
                    (float)x * TileUnit, (float)y * TileUnit,
                    TileUnit, TileUnit};
                if (CheckCollisionRecs(wallRec, rec))
                {
                    return true;
                }
            }
        }
    }

    return false;
}