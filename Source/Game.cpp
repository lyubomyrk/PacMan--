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

#include "Game.hpp"
#include "Globals.hpp"
#include "AssetManager.hpp"

using namespace std;

Game::Game()
{
}

bool Game::Init()
{
    InitWindow(WindowWidth, WindowHeight, WindowTitle.c_str());
    if (!IsWindowReady())
    {
        cout << "Failed to create a window.\n";
        return false;
    }
    SetTargetFPS(TargetFps);

    InitAudioDevice();
    if (!IsAudioDeviceReady())
    {
        cout << "Failed to initialize audio system.\n";
        return false;
    }

    if (!AssetManager::LoadAllAssets())
    {
        cout << "Failed to load assets.\n";
        return false;
    }

    initBoard();
    _movementComponent = new MovementComponent();
    _pacman = new PacMan(_movementComponent);

    return true;
}

bool Game::ShouldExit()
{
    return WindowShouldClose();
}

void Game::Update()
{
    _pacman->HandleInput();
    _pacman->Update();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(2, 2);
    DrawTexture(AssetManager::TBoard24, 0, 0, BLUE);
    _pacman->Draw();
    EndDrawing();
}

void Game::Cleanup()
{
    delete _pacman;

    AssetManager::UnloadAllAssets();

    CloseAudioDevice();
    CloseWindow();
}

void Game::initBoard()
{
    for (int i = 0; i < BoardRows; i++)
    {
        _gameBoard.push_back(vector<Tile>());
        for (int j = 0; j < BoardColumns; j++)
        {
            _gameBoard[i].push_back((Tile)Board[i][j]);
        }
    }
}