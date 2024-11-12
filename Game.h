#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Vec2.h"
#include "Scene.h"
#include <string>
#include <vector>
class Game
{
public:
	Game(std::string pTitle = "Game", std::vector<Scene*> scenes = {});
	Game(const Game&) = delete;
	void Initialize();

protected:
	std::string mTitle;
	Window* mWindow;
	Renderer* mRenderer;
	bool mIsRunning;

	std::vector<Scene*> mScenes;
	int mLoadedScene = 0;

	void Loop();
	void Render();
	void Update();
	void CheckInputs();
	void Close();

};

