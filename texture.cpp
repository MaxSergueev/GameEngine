#include "Texture.h"

Texture::Texture()
    : mFileName(""), mSdlTexture(nullptr), mWidth(0), mHeight(0)
{
}

Texture::~Texture() {
 //Unload();
}

bool Texture::Load(Renderer& pRenderer, const std::string& pFileName) {
    mFileName = pFileName;
    SDL_Surface* surface = IMG_Load(mFileName.c_str());
    if (!surface) {
        Log::Error(LogType::Application, "Failed to load texture file :" + mFileName);
        return false;
    }
    mWidth = surface->w;
    mHeight = surface->h;

    // Create texture from surface
    mSdlTexture = SDL_CreateTextureFromSurface(pRenderer.ToSdlRenderer(), surface);
    SDL_FreeSurface(surface);
    if (!mSdlTexture) {
        Log::Error(LogType::Render, "Failed to convert surface to texture :" + mFileName);
        return false;
    }
    Log::Info("Loaded texture : " + mFileName);
    return true;
}

void Texture::Unload() {
    if (mSdlTexture) {
        SDL_DestroyTexture(mSdlTexture);
    }
}

void Texture::UpdateInfo(int& width, int& height) {
    width = mWidth;
    height = mHeight;
}

int Texture::GetWidth() const {
    return mWidth;
}

int Texture::GetHeight() const {
    return mHeight;
}