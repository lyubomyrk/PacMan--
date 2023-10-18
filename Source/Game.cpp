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

    return true;
}

bool Game::ShouldExit()
{
    return WindowShouldClose();
}

void Game::Update()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(2, 2);
    DrawTexture(AssetManager::TBoard24, 0, 0, BLUE);
    EndDrawing();
}

void Game::Cleanup()
{
    CloseAudioDevice();
    CloseWindow();
}
