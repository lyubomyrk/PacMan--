#include "AssetManager.hpp"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

fs::path FindAssetsPath();
string AppendPathToString(fs::path p, string s);

const fs::path AssetsPath = FindAssetsPath();

bool AssetManager::LoadAllAssets()
{
    // Attempt to find absolute path to Assets directory
    if (AssetsPath.empty())
        return false;

    return LoadAllTextures() && LoadAllSounds() && LoadAllFonts();
}

bool AssetManager::LoadAllTextures()
{
    string TexturesPath = AppendPathToString(AssetsPath, "Textures");

    AssetManager::TBoard24 = LoadTexture((TexturesPath + "Map24.png").c_str());
    if (!IsTextureReady(AssetManager::TBoard24))
        return false;

    AssetManager::TPellet24 = LoadTexture((TexturesPath + "Pellet24.png").c_str());
    if (!IsTextureReady(AssetManager::TPellet24))
        return false;

    AssetManager::TEnergizer24 = LoadTexture((TexturesPath + "Energizer24.png").c_str());
    if (!IsTextureReady(AssetManager::TEnergizer24))
        return false;

    AssetManager::TDoor = LoadTexture((TexturesPath + "Door.png").c_str());
    if (!IsTextureReady(AssetManager::TDoor))
        return false;

    AssetManager::TFruit32 = LoadTexture((TexturesPath + "Fruit32.png").c_str());
    if (!IsTextureReady(AssetManager::TFruit32))
        return false;

    AssetManager::TPacMan32 = LoadTexture((TexturesPath + "PacMan32.png").c_str());
    if (!IsTextureReady(AssetManager::TPacMan32))
        return false;

    AssetManager::TPacManDeath32 = LoadTexture((TexturesPath + "PacManDeath32.png").c_str());
    if (!IsTextureReady(AssetManager::TPacManDeath32))
        return false;

    AssetManager::TGhostBody32 = LoadTexture((TexturesPath + "GhostBody32.png").c_str());
    if (!IsTextureReady(AssetManager::TGhostBody32))
        return false;

    AssetManager::TGhostEyes32 = LoadTexture((TexturesPath + "GhostEyes32.png").c_str());
    if (!IsTextureReady(AssetManager::TGhostEyes32))
        return false;

    return true;
}

bool AssetManager::LoadAllSounds()
{
    string SoundsPath = AppendPathToString(AssetsPath, "Sounds");

    AssetManager::SGameIntro = LoadSound((SoundsPath + "GameIntro.wav").c_str());
    if (!IsSoundReady(AssetManager::SGameIntro))
        return false;

    AssetManager::SWaka = LoadSound((SoundsPath + "Waka.wav").c_str());
    if (!IsSoundReady(AssetManager::SWaka))
        return false;

    AssetManager::SSiren = LoadSound((SoundsPath + "Siren.wav").c_str());
    if (!IsSoundReady(AssetManager::SSiren))
        return false;

    return true;
}

bool AssetManager::LoadAllFonts()
{
    string FontsPath = AppendPathToString(AssetsPath, "Fonts");

    AssetManager::FEmulogic = LoadFont((FontsPath + "Emulogic.ttf").c_str());
    if (!IsFontReady(AssetManager::FEmulogic))
        return false;

    return true;
}

void AssetManager::UnloadAllAssets()
{
    UnloadAllTextures();
    UnloadAllSounds();
    UnloadAllFonts();
}

void AssetManager::UnloadAllTextures()
{
    UnloadTexture(AssetManager::TBoard24);
    UnloadTexture(AssetManager::TPellet24);
    UnloadTexture(AssetManager::TDoor);
    UnloadTexture(AssetManager::TFruit32);
    UnloadTexture(AssetManager::TPacMan32);
    UnloadTexture(AssetManager::TPacManDeath32);
    UnloadTexture(AssetManager::TGhostBody32);
    UnloadTexture(AssetManager::TGhostEyes32);
}

void AssetManager::UnloadAllSounds()
{
    UnloadSound(AssetManager::SGameIntro);
    UnloadSound(AssetManager::SWaka);
    UnloadSound(AssetManager::SSiren);
}

void AssetManager::UnloadAllFonts()
{
    UnloadFont(AssetManager::FEmulogic);
}

const int MaxFileSystemWalkingDistance = 5;
fs::path FindAssetsPath()
{
    // Attempt to locate Assets directory by walking file system up
    fs::path currentPath = fs::current_path();

    for (int i = 0; i < MaxFileSystemWalkingDistance; i++)
    {
        fs::path assetsPath = currentPath / "Assets";
        if (fs::exists(assetsPath) && fs::is_directory(assetsPath))
            return assetsPath;

        currentPath = currentPath.parent_path();
    }

    // Return empty path if not found
    return "";
}
// Return new directory under the s string
string AppendPathToString(fs::path p, string s)
{
    return (p / s / "").string();
}