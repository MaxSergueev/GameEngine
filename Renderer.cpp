#include "Renderer.h"
#include "Log.h"
#include <vector>

Renderer::Renderer() :mSdlRenderer(nullptr)
{
}

bool Renderer::Initialize(Window& rWindow)
{
    mSdlRenderer = SDL_CreateRenderer(rWindow.GetSdlWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mSdlRenderer)
    {
        Log::Error(LogType::Video, "Failed to create Renderer");
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        Log::Error(LogType::Video, "Unable to initialize SDL_Image");
        return false;
    }

    return true;
}

void Renderer::BeginDraw()
{
    SDL_SetRenderDrawColor(mSdlRenderer, 120, 120, 255, 255);
    SDL_RenderClear(mSdlRenderer);
}

void Renderer::Draw()
{
    DrawSprites();
}

void Renderer::EndDraw()
{
    SDL_RenderPresent(mSdlRenderer);
}

void Renderer::Close()
{
    SDL_DestroyRenderer(mSdlRenderer);
}

void Renderer::DrawSprites()
{
    for (auto sprite : mSprites)
    {
        sprite->Draw(*this);
    }
}

void Renderer::DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip) const
{
    SDL_Rect destinationRect;
    Transform2D transform = pActor.GetTransform();

    float scaleX, scaleY;
	transform.GetScale(scaleX, scaleY);
    destinationRect.w = static_cast<int>(pTex.GetWidth() * scaleX);
    destinationRect.h = static_cast<int>(pTex.GetHeight() * scaleY);

    float posX, posY;
	transform.GetPosition(posX, posY);
    destinationRect.x = static_cast<int>(posX - pOrigin.x);
    destinationRect.y = static_cast<int>(posY - pOrigin.y);

    SDL_Rect* sourceSDL = nullptr;
    if (pSourceRect != Rectangle::NullRect)
    {
        sourceSDL = new SDL_Rect{
            Maths::Round(pSourceRect.position.x),
            Maths::Round(pSourceRect.position.y),
            Maths::Round(pSourceRect.dimensions.x),
            Maths::Round(pSourceRect.dimensions.y) };
    }
    SDL_RenderCopyEx(mSdlRenderer,
        pTex.GetSdlTexture(),
        sourceSDL,
        &destinationRect,
        -Maths::ToDeg(transform.GetRotation()),
        nullptr,
        SDL_FLIP_NONE);

    delete sourceSDL;
}

void Renderer::AddSprite(SpriteComponent* pSprite)
{
    int spriteDrawOrder = pSprite->GetDrawOrder();
    std::vector<SpriteComponent*>::iterator sc;
    for (sc = mSprites.begin(); sc != mSprites.end(); ++sc)
    {
        if (spriteDrawOrder < (*sc)->GetDrawOrder()) break;
    }
    mSprites.insert(sc, pSprite);
}


void Renderer::RemoveSprite(SpriteComponent* pSprite)
{
    std::vector<SpriteComponent*>::iterator sc;
    sc = std::find(mSprites.begin(), mSprites.end(), pSprite);
    mSprites.erase(sc);
}



void Renderer::DrawRect(Rectangle& rRect)
{
    SDL_SetRenderDrawColor(mSdlRenderer, 255, 255, 255, 255);
    SDL_Rect sdlRect = rRect.ToSdlRect();
    SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}


