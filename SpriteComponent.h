#pragma once
#include "Component.h"
//#include "Texture.h"

class Texture;

class SpriteComponent : public Component
{
protected:
	Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
public:
	SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder = 100);
	virtual ~SpriteComponent();
	SpriteComponent() = delete;
	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent& operator= (const SpriteComponent&) = delete;

	virtual void OnStart() override;

	virtual void SetTexture(const Texture& pTexture);
	virtual void Draw(Renderer& pRenderer);

	//Getters
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }
};

