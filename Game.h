#pragma once
#include "Window.h"
#include "Renderer.h"
#include <string>
class Game
{
public:
	Game(std::string pTitle = "Game");
	Game(const Game&) = delete;
	void Initialize();

protected:
	std::string mTitle;
	Window* mWindow;
	Renderer* mRenderer;
	bool mIsRunning;

	

	void Loop();
	void Render();
	void Update();
	void CheckInputs();
	void Close();

};

