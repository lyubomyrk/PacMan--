#pragma once

class Game
{

public:
    Game();

    bool Init();
    bool ShouldExit();
    void Update();
    void Cleanup();

private:
};