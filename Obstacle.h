#pragma once
#include "Actor.h"
#include "BoxCollider2D.h"
class Obstacle : public Actor {
public:
    Obstacle(Scene* scene) : Actor(scene) {
        BoxCollider2D* collider = AddComponent<BoxCollider2D>();
        collider->SetSize(100.0f, 100.0f);
    }

    void OnStart() override {
        Actor::OnStart();
    }
};