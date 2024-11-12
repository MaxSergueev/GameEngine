#include "Scene.h"

Scene::Scene(const std::string& pTitle) : title(pTitle), mRenderer(nullptr) {}

void Scene::SetRenderer(Renderer* renderer)
{
    this->mRenderer = renderer;
}

void Scene::Start()
{
}

void Scene::Update()
{
}

void Scene::Render()
{
}

void Scene::OnInput(const SDL_Event& event)
{
}

void Scene::Close()
{
}

std::string Scene::GetTitle() const
{
    return std::string();
}