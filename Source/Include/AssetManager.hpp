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

class AssetManager
{
public:
    static bool LoadAllAssets();
    static bool LoadAllTextures();
    static bool LoadAllSounds();
    static bool LoadAllFonts();
    static void UnloadAllAssets();
    static void UnloadAllTextures();
    static void UnloadAllSounds();
    static void UnloadAllFonts();

    inline static Texture2D TBoard24;
    inline static Texture2D TPellet24;
    inline static Texture2D TEnergizer24;
    inline static Texture2D TDoor;
    inline static Texture2D TFruit32;

    inline static Texture2D TPacMan32;
    inline static Texture2D TPacManDeath32;

    inline static Texture2D TGhostBody32;
    inline static Texture2D TGhostEyes32;

    inline static Sound SGameIntro;
    inline static Sound SWaka;
    inline static Sound SSiren;

    inline static Font FEmulogic;

private:
};