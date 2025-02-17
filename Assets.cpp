#include "Assets.h"
#include <sstream>
#include "Log.h"

// Define the static map that holds the textures.
std::map<std::string, Texture> Assets::mTextures = {};

// LoadTexture:
// Loads a texture from a file using the helper function, stores it in the mTextures map
// using the key pName, and returns a copy of the texture.
Texture Assets::LoadTexture(Renderer& pRenderer, const std::string& pFileName, const std::string& pName)
{
    mTextures[pName] = LoadTextureFromFile(pRenderer, pFileName);
    return mTextures[pName];
}

// GetTexture:
// Retrieves a texture from the mTextures map by name.
// If the texture is not found, an error is logged.
Texture& Assets::GetTexture(const std::string& pName)
{
    if (mTextures.find(pName) == mTextures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture " << pName << " does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
    }
    return mTextures[pName];
}

// Clear:
// Iterates over all stored textures, calling Unload() on each one,
// then clears the mTextures map.
void Assets::Clear()
{
    for (auto iter : mTextures)
    {
        iter.second.Unload();
    }
    mTextures.clear();
}

// LoadTextureFromFile:
// A helper function that creates a Texture object, loads the texture from file using the given renderer,
// and returns the loaded texture.
Texture Assets::LoadTextureFromFile(Renderer& pRenderer, const std::string& pFileName)
{
    Texture texture;
    texture.Load(pRenderer, pFileName);
    return texture;
}
