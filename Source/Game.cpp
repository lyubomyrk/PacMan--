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
#include "ScatterGhostDirectionComponent.hpp"
#include "RandomDirectionComponent.hpp"

using namespace std;

Game::Game()
{
    _gameBoard = nullptr;
    _playerDirectionComponent = nullptr;
    _blinkyChaseDirectionComponent = nullptr;
    _pinkyChaseDirectionComponent = nullptr;
    _inkyChaseDirectionComponent = nullptr;
    _clydeChaseDirectionComponent = nullptr;
    _movementComponent = nullptr;
    _ghosts.clear();
    _pacman = nullptr;
    _blinky = nullptr;
    _pinky = nullptr;
    _inky = nullptr;
    _clyde = nullptr;

    _active = false;
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

    _playerDirectionComponent = new PlayerDirectionComponent(_gameBoard);
    _movementComponent = new MovementComponent(_gameBoard);

    _pacman = new PacMan(_playerDirectionComponent, _movementComponent);

    _randomDirectionComponent = new RandomDirectionComponent(_gameBoard);

    _blinkyScatterDirectionComponent = new ScatterGhostDirectionComponent(_gameBoard, RedGhostScatterTargetPosition);
    _blinkyChaseDirectionComponent = new BlinkyDirectionComponent(_gameBoard, _pacman);
    _blinky = new Ghost(
        RED,
        RedGhostStartingPosition,
        Direction::Left(),
        _blinkyScatterDirectionComponent,
        _blinkyChaseDirectionComponent,
        _randomDirectionComponent,
        _movementComponent);

    _pinkyScatterDirectionComponent = new ScatterGhostDirectionComponent(_gameBoard, PinkGhostScatterTargetPosition);
    _pinkyChaseDirectionComponent = new PinkyDirectionComponent(_gameBoard, _pacman);
    _pinky = new Ghost(
        PINK,
        RedGhostStartingPosition,
        Direction::Right(),
        _pinkyScatterDirectionComponent,
        _pinkyChaseDirectionComponent,
        _randomDirectionComponent,
        _movementComponent);

    _inkyScatterDirectionComponent = new ScatterGhostDirectionComponent(_gameBoard, BlueGhostScatterTargetPosition);
    _inkyChaseDirectionComponent = new InkyDirectionComponent(_gameBoard, _pacman, _blinky);
    _inky = new Ghost(
        SKYBLUE,
        RedGhostStartingPosition,
        Direction::Right(),
        _inkyScatterDirectionComponent,
        _inkyChaseDirectionComponent,
        _randomDirectionComponent,
        _movementComponent);

    _clydeScatterDirectionComponent = new ScatterGhostDirectionComponent(_gameBoard, OrangeGhostScatterTargetPosition);
    _clydeChaseDirectionComponent = new ClydeDirectionComponent(_gameBoard, _pacman);
    _clyde = new Ghost(
        ORANGE,
        RedGhostStartingPosition,
        Direction::Left(),
        _clydeScatterDirectionComponent,
        _clydeChaseDirectionComponent,
        _randomDirectionComponent,
        _movementComponent);

    _ghosts.push_back(_blinky);
    _ghosts.push_back(_pinky);
    _ghosts.push_back(_inky);
    _ghosts.push_back(_clyde);

    nextLevel();

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
    for (Ghost *ghost : _ghosts)
    {
        ghost->HandleInput();
    }
    _pacman->HandleInput();

    /**
     * Update entities.
     */
    for (Ghost *ghost : _ghosts)
    {
        ghost->Update();
    }
    _pacman->Update();

    _introTimer.Update();

    /**
     * Handle game conditions.
     */
    if (!_active && _introTimer.IsFinished())
    {
        _pacman->Start();
        for (Ghost *ghost : _ghosts)
        {
            ghost->Start();
        }

        _active = true;
    }

    Vector2 pacmanPos = _pacman->GetPosition();
    Vector2 pacmanTile = {
        floor(pacmanPos.x / TileUnit), floor(pacmanPos.y / TileUnit)};
    Vector2 pacmanDir = _pacman->GetDirection();

    for (Ghost *ghost : _ghosts)
    {
        Vector2 ghostPos = ghost->GetPosition();
        Vector2 ghostTile = {
            floor(ghostPos.x / TileUnit), floor(ghostPos.y / TileUnit)};

        if (pacmanTile == ghostTile && !_pacman->IsEnergized())
        {
            _pacman->Kill();
            for (Ghost *ghost : _ghosts)
            {
                ghost->Stop();
            }
            break;
        }
    }

    // Check if eaten pellet.
    if (_gameBoard->IsThere(pacmanPos, Tile::Pellet))
    {
        _gameBoard->Remove(pacmanPos, Tile::Pellet);
        _pacman->AtePellet();
    }
    if (_gameBoard->IsThere(pacmanPos, Tile::Energizer))
    {
        _gameBoard->Remove(pacmanPos, Tile::Energizer);
        _pacman->Energize();
        for (Ghost *ghost : _ghosts)
        {
            ghost->Frighten();
        }
    }

    if (_gameBoard->Pellets() == 0)
    {
        nextLevel();
    }
    if (!_pacman->IsAlive() && _pacman->IsDeathFinished())
    {
        nextLife();
    }

    /**
     * Play audio.
     */
    PlaySoundIfTrue(AssetManager::SGameIntro, !_active && _pacman->IsAlive());
    PlaySoundIfTrue(AssetManager::SSiren, _active && _pacman->IsAlive());
}

void Game::Draw()
{
    /**
     * Draw.
     */
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(2, 2);
    _gameBoard->Draw();
    for (Ghost *ghost : _ghosts)
    {
        ghost->Draw();
    }
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
    if (_blinkyScatterDirectionComponent)
        delete _blinkyScatterDirectionComponent;
    if (_pinkyScatterDirectionComponent)
        delete _pinkyScatterDirectionComponent;
    if (_inkyScatterDirectionComponent)
        delete _inkyScatterDirectionComponent;
    if (_clydeScatterDirectionComponent)
        delete _clydeScatterDirectionComponent;
    if (_blinkyChaseDirectionComponent)
        delete _blinkyChaseDirectionComponent;
    if (_pinkyChaseDirectionComponent)
        delete _pinkyChaseDirectionComponent;
    if (_inkyChaseDirectionComponent)
        delete _inkyChaseDirectionComponent;
    if (_clydeChaseDirectionComponent)
        delete _clydeChaseDirectionComponent;
    if (_randomDirectionComponent)
        delete _randomDirectionComponent;
    if (_gameBoard)
        delete _gameBoard;

    AssetManager::UnloadAllAssets();

    CloseAudioDevice();
    CloseWindow();
}

void Game::nextLevel()
{
    _gameBoard->Reset();
    nextLife();
}

void Game::nextLife()
{
    _pacman->Reset();
    for (Ghost *ghost : _ghosts)
    {
        ghost->Reset();
    }

    _introTimer.Start(IntroTime);
    _active = false;
}
