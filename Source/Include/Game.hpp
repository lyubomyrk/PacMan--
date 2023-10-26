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

#include "Globals.hpp"
#include "GameBoard.hpp"
#include "DirectionComponent.hpp"
#include "PlayerDirectionComponent.hpp"
#include "BlinkyDirectionComponent.hpp"
#include "PinkyDirectionComponent.hpp"
#include "InkyDirectionComponent.hpp"
#include "ClydeDirectionComponent.hpp"
#include "MovementComponent.hpp"
#include "PacMan.hpp"
#include "Ghost.hpp"
#include "Timer.hpp"

class Game
{
    GameBoard *_gameBoard;

    DirectionComponent *_playerDirectionComponent;
    DirectionComponent *_blinkyDirectionComponent;
    DirectionComponent *_pinkyDirectionComponent;
    DirectionComponent *_inkyDirectionComponent;
    DirectionComponent *_clydeDirectionComponent;
    MovementComponent *_movementComponent;
    PacMan *_pacman;
    vector<Ghost *> _ghosts;
    Ghost *_blinky;
    Ghost *_pinky;
    Ghost *_inky;
    Ghost *_clyde;

    Timer _introTimer;

    bool _active;

public:
    Game();

    /**
     * Initialize graphics and audio, load assets, and setup
     * game state for first level and play.
     *
     * @return true if game initialized successfully, false otherwise
     */
    bool Init();
    /**
     * Return if game should exit.
     *
     * @return true if game should exit, false otherwise
     */
    bool ShouldExit();
    /**
     * Update and draw one frame.
     */
    void Update();
    void Draw();
    void Cleanup();

private:
    void nextLevel();
    void nextLife();
};