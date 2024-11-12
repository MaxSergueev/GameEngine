#pragma once
#include <SDL.h>
#include "Vec2.h"

class Window
{
private:
	SDL_Window* mSdlWindow;
	Vector2 mDimensions;
public:
	Window(int pWidth = 800, int pHeight = 800);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Vector2 GetDimensions() const { return mDimensions; };

	SDL_Window* GetSdlWindow() const { return mSdlWindow; };

	bool Open();
	void Close();
};
