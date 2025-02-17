#pragma once
#include "Rectangle.h"
#include "Window.h"
#include "SDL_image.h"
#include <vector>
#include "Actor.h"
#include "Texture.h"
#include "math.h"
#include "SpriteComponent.h"

enum class Flip
{
	None = SDL_FLIP_NONE,
	Horizontal = SDL_FLIP_HORIZONTAL,
	Vertical = SDL_FLIP_VERTICAL
};

class Renderer
{
private:
	SDL_Renderer* mSdlRenderer;
	std::vector<SpriteComponent*> mSprites;
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator= (const Renderer&) = delete;

	bool Initialize(Window& rWindow);
	void BeginDraw();
	void Draw();
	void EndDraw();
	void Close();
	
	void DrawSprites(); // to draw all sprites in the renderer
	void DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip) const;

	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);

	SDL_Renderer* ToSdlRenderer() const { return mSdlRenderer; }

	void DrawRect(Rectangle& rRect);
};

