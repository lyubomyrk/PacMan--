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
#include "AssetManager.hpp"

GameBoard::GameBoard()
{
    _pellets = 0;
}

GameBoard::~GameBoard()
{
}

void GameBoard::Draw()
{
    // Draw maze.
    DrawTexture(AssetManager::TBoard24, 0, 0, BLUE);

    // Draw pellets and energizer.
    for (int i = 0; i < BoardRows; i++)
    {
        for (int j = 0; j < BoardColumns; j++)
        {
            if (_gameBoard[i][j] == Tile::Pellet)
            {
                DrawTexture(AssetManager::TPellet24, j * TileUnit, i * TileUnit, WHITE);
            }
        }
    }

    if constexpr (DEBUG)
    {
        drawDebugRecs();
    }
}

void GameBoard::Reset()
{
    _gameBoard.clear();

    for (int m = 0; m < BoardRows; m++)
    {
        vector<Tile> row;

        for (int n = 0; n < BoardColumns; n++)
        {
            switch (Board[m][n])
            {
            case (char)Tile::Pellet:
                _pellets++;
                break;
            }
            row.push_back((Tile)Board[m][n]);
        }

        _gameBoard.push_back(row);
    }
}

bool GameBoard::IsThereWall(Vector2 position)
{
    return IsThere(position, Tile::Wall) || IsThere(position, Tile::Door);
}

bool GameBoard::IsThere(Vector2 position, Tile tile)
{
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

    if constexpr (DEBUG)
    {
        Rectangle debugRec = {(float)boundingLeft * TileUnit, (float)boundingTop * TileUnit,
                              (float)(boundingRight - boundingLeft) * TileUnit, (float)(boundingBottom - boundingTop) * TileUnit};

        _debugCollisionRecs.push_back(debugRec);
    }

    for (int y = boundingTop; y <= boundingBottom; y++)
    {
        for (int x = boundingLeft; x <= boundingRight; x++)
        {
            if (_gameBoard[y][x] == tile)
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

void GameBoard::Remove(Vector2 position, Tile type)
{
    Vector2 tile = {
        floor(position.x / TileUnit), floor(position.y / TileUnit)};

    if (_gameBoard[(int)tile.y][(int)tile.x] == type)
    {
        switch (type)
        {
        case Tile::Pellet:
            _pellets--;
            break;
        default:
            break;
        }
        _gameBoard[(int)tile.y][(int)tile.x] = Tile::Empty;
    }
}

void GameBoard::AddDebugRec(Vector2 position)
{
    Rectangle debugColRec = {
        position.x - TileUnitOffset, position.y - TileUnitOffset,
        (float)TileUnit, (float)TileUnit};

    _debugCollisionRecs.push_back(debugColRec);
}

int GameBoard::Pellets() const
{
    return _pellets;
}

void GameBoard::drawDebugRecs()
{
    for (Rectangle colRec : _debugCollisionRecs)
    {
        DrawRectangleLines(colRec.x, colRec.y, colRec.width, colRec.height, GREEN);
    }

    _debugCollisionRecs.clear();
}
