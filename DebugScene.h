#pragma once
#include "Scene.h"
#include "Renderer.h"

class DebugScene : public Scene {
private:
    float leftPaddleX, leftPaddleY;
    float rightPaddleX, rightPaddleY;
    float paddleWidth, paddleHeight, paddleSpeed, paddleMoveL, paddleMoveR;

    float ballX, ballY;
    float ballVelocityX, ballVelocityY;
    float ballRadius, ballSpeed;

public:
    DebugScene(const std::string& title);

    void Start() override;
	virtual void Load() override;
    void Update() override;
    void Render() override;
    void OnInput(const SDL_Event& event) override;
    void Close() override;
};