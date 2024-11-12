#include "Game.h"
#include "Rectangle.h"
Game::Game(std::string pTitle) :mIsRunning(true)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!";
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
    Rectangle rectangle = { {200, 200},{200, 200} };
    mRenderer->DrawRect(rectangle);

    mRenderer->EndDraw();
}

void Game::Update()
{
}

void Game::CheckInputs()
{
    if (mIsRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                //Send input to scene
                break;
            }
        }
    }
}

void Game::Close()
{
    mWindow->Close();
}
