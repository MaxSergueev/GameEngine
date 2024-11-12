#include "Game.h"
#include "Rectangle.h"

Game::Game(std::string pTitle, std::vector<Scene*> scenes)
    : mTitle(pTitle), mIsRunning(true), mScenes(scenes) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else {
        std::cout << "SDL initialization succeeded!";
    }
    if (!mScenes.empty()) {
        mScenes[mLoadedScene]->SetRenderer(mRenderer);
        mScenes[mLoadedScene]->Start();
    }
    Initialize();
}

void Game::Initialize()
{
    mWindow = new Window(800, 800);
    mRenderer = new Renderer();
    if (mWindow->Open() &&mRenderer->Initialize(*mWindow)) Loop();
}

void Game::Loop()
{
    while (mIsRunning) {
        CheckInputs();
        Update();
        Render();

    }
    Close();
}

void Game::Render()
{
        mRenderer->BeginDraw();
        mScenes[mLoadedScene]->Render();
        mRenderer->EndDraw();
}

void Game::Update()
{
    if (!mScenes.empty()) {
        mScenes[mLoadedScene]->Update();
    }
}

void Game::CheckInputs() {
    if (mIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                if (!mScenes.empty()) {
                    mScenes[mLoadedScene]->OnInput(event);
                }
                break;
            }
        }
    }
}

void Game::Close()
{
    if (!mScenes.empty()) {
        mScenes[mLoadedScene]->Close();
    }
    mWindow->Close();
}
