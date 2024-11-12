#pragma once
#include <string>
#include <SDL.h>
#include "Renderer.h"

class Scene {
public:
    Scene(const std::string& pTitle = "Scene");

    virtual void SetRenderer(Renderer* renderer);
    virtual void Start();
    virtual void Update();
    virtual void Render();
    virtual void OnInput(const SDL_Event& event);
    virtual void Close();

    std::string GetTitle() const;

protected:
    std::string title;
    Renderer* mRenderer;
};
