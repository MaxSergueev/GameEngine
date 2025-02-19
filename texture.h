#pragma once
#include <cmath>
#include <iostream>
#include <string>

#include "Renderer.h"

#include "SDL.h"
#include "SDL_image.h"
#include "Log.h"

class Texture {
public:
    Texture();
    ~Texture();// = default;

    bool Load(Renderer& pRenderer, const std::string& pFileName);

    void Unload();

    void UpdateInfo(int& width, int& height);

    int GetWidth() const;

    int GetHeight() const;

	inline SDL_Texture* GetSdlTexture() const { return mSdlTexture; }

private:
    std::string mFileName;
    SDL_Texture* mSdlTexture;
    int mWidth;
    int mHeight;
};

