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
    _gameBoard = nullptr;
    _playerDirectionComponent = nullptr;
    _blinkyDirectionComponent = nullptr;
    _pinkyDirectionComponent = nullptr;
    _inkyDirectionComponent = nullptr;
    _clydeDirectionComponent = nullptr;
    _movementComponent = nullptr;
    _pacman = nullptr;
    _blinky = nullptr;
    _pinky = nullptr;
    _inky = nullptr;
    _clyde = nullptr;
    _prevPacmanPos = {0};
    _prevPacmanDir = {0};
    _playSiren = false;
    _playWaka = false;
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

    _gameBoard = new GameBoard();
    _gameBoard->Reset();

    _playerDirectionComponent = new PlayerDirectionComponent(_gameBoard);
    _movementComponent = new MovementComponent(_gameBoard);

    _pacman = new PacMan(_playerDirectionComponent, _movementComponent);

    _blinkyDirectionComponent = new BlinkyDirectionComponent(_gameBoard, _pacman);
    _blinky = new Ghost(
        RED,
        RedGhostStartingPosition,
        Direction::Left(),
        _blinkyDirectionComponent,
        _movementComponent);

    _pinkyDirectionComponent = new PinkyDirectionComponent(_gameBoard, _pacman);
    _pinky = new Ghost(
        PINK,
        RedGhostStartingPosition,
        Direction::Right(),
        _pinkyDirectionComponent,
        _movementComponent);

    _inkyDirectionComponent = new InkyDirectionComponent(_gameBoard, _pacman, _blinky);
    _inky = new Ghost(
        SKYBLUE,
        RedGhostStartingPosition,
        Direction::Right(),
        _inkyDirectionComponent,
        _movementComponent);

    _clydeDirectionComponent = new ClydeDirectionComponent(_gameBoard, _pacman);
    _clyde = new Ghost(
        ORANGE,
        RedGhostStartingPosition,
        Direction::Left(),
        _clydeDirectionComponent,
        _movementComponent);

    return true;
}

bool Game::ShouldExit()
{
    return WindowShouldClose();
}

void Game::Update()
{
    /**
     * Handle entity input.
     */
    _blinky->HandleInput();
    _pinky->HandleInput();
    _inky->HandleInput();
    _clyde->HandleInput();
    _pacman->HandleInput();

    /**
     * Update entities.
     */
    _blinky->Update();
    _pinky->Update();
    _inky->Update();
    _clyde->Update();
    _pacman->Update();

    /**
     * Handle game conditions.
     */

    Vector2 pacmanPos = _pacman->GetPosition();
    Vector2 pacmanTile = {
        floor(pacmanPos.x / TileUnit), floor(pacmanPos.y / TileUnit)};
    Vector2 pacmanDir = _pacman->GetDirection();

    Vector2 prevPacmanTile = {
        floor(_prevPacmanPos.x / TileUnit), floor(_prevPacmanPos.y / TileUnit)};

    // Pacman on new tile.
    if (pacmanTile != prevPacmanTile)
    {
        if (_gameBoard->IsThere(pacmanPos, Tile::Empty))
        {
            _playWaka = false;
        }
    }
    // Pacman changes direction.
    if (pacmanDir != _prevPacmanDir)
    {
        if (_gameBoard->IsThere(pacmanPos, Tile::Empty))
        {
            _playWaka = false;
        }
    }
    // Pacman hit a wall.
    if (pacmanPos == _prevPacmanPos)
    {
        _playWaka = false;
    }

    // Check if eaten pellet.
    if (_gameBoard->IsThere(pacmanPos, Tile::Pellet))
    {
        _gameBoard->Remove(pacmanPos, Tile::Pellet);
        _playWaka = true;
    }

    if (_pacman->IsAlive())
    {
        _playSiren = true;
    }
    else
    {
        _playSiren = false;
        _playWaka = false;
    }

    /**
     * Play audio.
     */
    if (_playSiren && !IsSoundPlaying(AssetManager::SSiren))
    {
        PlaySound(AssetManager::SSiren);
    }
    else if (!_playSiren && IsSoundPlaying(AssetManager::SSiren))
    {
        PlaySound(AssetManager::SSiren);
    }

    if (_playWaka && !IsSoundPlaying(AssetManager::SWaka))
    {
        PlaySound(AssetManager::SWaka);
    }
    else if (!_playWaka && IsSoundPlaying(AssetManager::SWaka))
    {
        StopSound(AssetManager::SWaka);
    }

    _prevPacmanPos = pacmanPos;
    _prevPacmanDir = pacmanDir;

    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(2, 2);
    _gameBoard->Draw();
    _blinky->Draw();
    _pinky->Draw();
    _inky->Draw();
    _clyde->Draw();
    _pacman->Draw();
    EndDrawing();
}

void Game::Cleanup()
{
    if (_clyde)
        delete _clyde;
    if (_inky)
        delete _inky;
    if (_pinky)
        delete _pinky;
    if (_blinky)
        delete _blinky;
    if (_pacman)
        delete _pacman;
    if (_movementComponent)
        delete _movementComponent;
    if (_playerDirectionComponent)
        delete _playerDirectionComponent;
    if (_blinkyDirectionComponent)
        delete _blinkyDirectionComponent;
    if (_pinkyDirectionComponent)
        delete _pinkyDirectionComponent;
    if (_inkyDirectionComponent)
        delete _inkyDirectionComponent;
    if (_clydeDirectionComponent)
        delete _clydeDirectionComponent;
    if (_gameBoard)
        delete _gameBoard;

    AssetManager::UnloadAllAssets();

    CloseAudioDevice();
    CloseWindow();
}
