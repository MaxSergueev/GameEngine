#include "DebugScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include <SDL.h>
#include <cmath>

DebugScene::DebugScene(const std::string& title) : Scene(title) {
}

void DebugScene::Start() {
    Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball"); //Resources/dirtblockh.png
	//AddActor(new Actor());
    //SpriteComponent* sprite = mActors[0]->AddComponent<SpriteComponent>(Assets::GetTexture("ball"), 0);
    Actor* actor = new Actor(this);
    SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));
    actor->GetTransform().SetPosition(500, 500);

    //mRenderer->AddSprite(sprite);
}

void DebugScene::Load() {
}

void DebugScene::Update() {
}

void DebugScene::Render() {
	mRenderer->BeginDraw();
    mRenderer->DrawSprites();
}

void DebugScene::OnInput(const SDL_Event& event) {

}
   

void DebugScene::Close() {
}