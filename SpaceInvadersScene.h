#pragma once
#include "Scene.h"
#include "SpacePlayer.h"
#include "Alien.h"
class SpaceInvadersScene : public Scene {
public:
    SpaceInvadersScene() : Scene("Space Invaders") {}

    void Initialize() override {
        // Create player
        SpacePlayer* player = new SpacePlayer(this);
        AddActor(player);

        // Create aliens
        for (int i = 0; i < 6; i++) {
            Alien* alien = new Alien(this);
            alien->GetTransform().SetPosition(
                150.0f + i * 100.0f,
                100.0f
            );
            AddActor(alien);
        }
    }

    void Render() override {
        for (auto actor : mActors) {
            BoxCollider2D* collider = actor->GetComponent<BoxCollider2D>();
            if (collider) {
                Rectangle rect;
                Vector2 pos = collider->GetWorldPosition();
                rect.position = Vector2(pos.x - collider->GetWidth() / 2.0f,
                    pos.y - collider->GetHeight() / 2.0f);
                rect.dimensions = Vector2(collider->GetWidth(), collider->GetHeight());
                mRenderer->DrawRect(rect);
            }
        }
    }
};