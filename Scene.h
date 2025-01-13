#pragma once
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Renderer.h"
#include "Actor.h"

class Scene {
public:
    Scene(const std::string& pTitle = "Scene");
    virtual ~Scene();

    virtual void SetRenderer(Renderer* renderer);
    virtual void Start();
    virtual void Update();
    virtual void Render();
    virtual void OnInput(const SDL_Event& event);
    virtual void Close();
    virtual void Initialize();

    std::string GetTitle() const;

    // Actor Management
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    const std::vector<Actor*>& GetActors() const { return mActors; }

protected:
    std::string title;
    Renderer* mRenderer;
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;  // Actors to be added next frame
    bool mUpdatingActors;  // Flag to prevent modifying actors during update
};
