#pragma once

#include <map>
#include <string>
#include "Texture.h"

class Assets
{
public:
    static std::map<std::string, Texture> mTextures;
    
    static Texture LoadTexture(Renderer& pRenderer, const std::string& pFileName, const std::string& pName);

    static Texture& GetTexture(const std::string& pName);

    static void Clear();

private:
    Assets() = default;
    static Texture LoadTextureFromFile(Renderer& pRenderer, const std::string& pFileName);
};
