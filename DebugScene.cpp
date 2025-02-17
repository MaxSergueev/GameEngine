#include "DebugScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include <SDL.h>
#include <cmath>

DebugScene::DebugScene(const std::string& title) : Scene(title) {
    leftPaddleX = 50;
    leftPaddleY = 300;
    rightPaddleX = 730;
    rightPaddleY = 300;
    paddleWidth = 20;
    paddleHeight = 100;
    paddleSpeed = 10;
    paddleMoveL = 0;
    paddleMoveR = 0;

    ballX = 400;
    ballY = 300;
    ballRadius = 10;
    ballSpeed = 5;
    ballVelocityX = ballSpeed;
    ballVelocityY = ballSpeed;
}

void DebugScene::Start() {
    Assets::LoadTexture(*mRenderer, "Resources/dirtblock.png", "ball");
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

    ballX += ballVelocityX;
    ballY += ballVelocityY;

    if (ballY <= 0 || ballY + ballRadius * 2 >= 800) {
        ballVelocityY = -ballVelocityY;
    }

    if (ballX <= leftPaddleX + paddleWidth &&
        ballY + ballRadius * 2 >= leftPaddleY &&
        ballY <= leftPaddleY + paddleHeight) {
        ballVelocityX = std::abs(ballVelocityX);
    }

    if (ballX + ballRadius * 2 >= rightPaddleX &&
        ballY + ballRadius * 2 >= rightPaddleY &&
        ballY <= rightPaddleY + paddleHeight) {
        ballVelocityX = -std::abs(ballVelocityX);
    }

    //Respawn
    if (ballX < 0 || ballX + ballRadius * 2 > 800) {
        ballX = 400 - ballRadius;
        ballY = 300 - ballRadius;
        ballVelocityX = (ballVelocityX > 0) ? -ballSpeed : ballSpeed;
    }

    //Moving Paddles
    leftPaddleY += paddleMoveL;
    rightPaddleY += paddleMoveR;
}

void DebugScene::Render() {
	mRenderer->BeginDraw();
    mRenderer->DrawSprites();
}

void DebugScene::OnInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            paddleMoveL = -1*paddleSpeed;
            break;
        case SDLK_s:
            paddleMoveL = paddleSpeed;
            break;
        case SDLK_UP:
            paddleMoveR = -1 * paddleSpeed;
            break;
        case SDLK_DOWN:
            paddleMoveR = paddleSpeed;
            break;
        }
    }
    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            paddleMoveL = 0;
            break;
        case SDLK_s:
            paddleMoveL = 0;
            break;
        case SDLK_UP:
            paddleMoveR = 0;
            break;
        case SDLK_DOWN:
            paddleMoveR = 0;
            break;
        }
    }
}
   

void DebugScene::Close() {
}