#include <iostream>
#include <SDL.h>
#include "Vec2.h"
#include "Log.h"
#include "Window.h"
#include "Game.h"
using namespace std;

int main(int argc, char* argv[])
{
	Game myGame("");
	myGame.Initialize();
	return 0;
}