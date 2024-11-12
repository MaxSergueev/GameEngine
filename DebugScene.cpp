#include "DebugScene.h"
#include <SDL.h>
#include <cmath>

DebugScene::DebugScene(const std::string& title) : Scene(title) {
    leftPaddleX = 50;
    leftPaddleY = 300;
    rightPaddleX = 730;
    rightPaddleY = 300;
    paddleWidth = 20;
    paddleHeight = 100;
    paddleSpeed = 50;

    ballX = 400;
    ballY = 300;
    ballRadius = 10;
    ballSpeed = 2;
    ballVelocityX = ballSpeed;
    ballVelocityY = ballSpeed;
}

void DebugScene::Start() {
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
}

void DebugScene::Render() {

    Rectangle leftPaddleRect = { {leftPaddleX, leftPaddleY}, {paddleWidth, paddleHeight} };
    mRenderer->DrawRect(leftPaddleRect);

    Rectangle rightPaddleRect = { {rightPaddleX, rightPaddleY}, {paddleWidth, paddleHeight} };
    mRenderer->DrawRect(rightPaddleRect);

    Rectangle ballRect = { {ballX, ballY}, {ballRadius * 2, ballRadius * 2} };
    mRenderer->DrawRect(ballRect);

}

void DebugScene::OnInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            leftPaddleY -= paddleSpeed;
            break;
        case SDLK_s:
            leftPaddleY += paddleSpeed;
            break;
        case SDLK_UP:
            rightPaddleY -= paddleSpeed;
            break;
        case SDLK_DOWN:
            rightPaddleY += paddleSpeed;
            break;
        }
    }
}

void DebugScene::Close() {
}