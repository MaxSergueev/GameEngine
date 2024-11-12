#include <iostream>
#include <SDL.h>
#include "Vec2.h"
#include "Log.h"
#include "Window.h"
#include "Game.h"
#include "DebugScene.h"
using namespace std;

int main(int argc, char* argv[])
{
    Game game("Debug Game", { new DebugScene("Hello")});
    game.Initialize();

    return 0;
}