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