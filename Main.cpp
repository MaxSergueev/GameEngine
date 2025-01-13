#include <iostream>
#include <SDL.h>
#include "Vec2.h"
#include "Log.h"
#include "Window.h"
#include "Game.h"
#include "DebugScene.h"
#include "SpaceInvadersScene.h"
using namespace std;

int main(int argc, char* argv[])
{
    //Game game("Debug Game", { new DebugScene("Hello")});
    SpaceInvadersScene* scene = new SpaceInvadersScene();
    scene->Initialize();
    Game game("Space invaders", { scene });
    game.Initialize();

    return 0;
}