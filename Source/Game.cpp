#include "Game.hpp"
#include "Globals.hpp"

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
    EndDrawing();
}

void Game::Cleanup()
{
    CloseAudioDevice();
    CloseWindow();
}
