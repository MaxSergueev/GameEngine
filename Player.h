#pragma once
#include "Actor.h"
#include "BoxCollider2D.h"
#include "Scene.h"
#include "Time.h"

class Player : public Actor {
public:
    Player(Scene* scene) : Actor(scene), mSpeed(300.0f) {
        // Add box collider and set its size
        mCollider = AddComponent<BoxCollider2D>();
        mCollider->SetSize(50.0f, 50.0f);
    }

    void OnUpdate() override {
        // Get current position
        float posX, posY;
        GetTransform().GetPosition(posX, posY);

        // Store original position in case we need to revert due to collision
        float originalX = posX;
        float originalY = posY;

        // Calculate movement
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
        float deltaX = 0.0f;
        float deltaY = 0.0f;

        if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]) {
            deltaY -= mSpeed * Time::deltaTime;
        }
        if (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]) {
            deltaY += mSpeed * Time::deltaTime;
        }
        if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
            deltaX -= mSpeed * Time::deltaTime;
        }
        if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
            deltaX += mSpeed * Time::deltaTime;
        }

        // Update position
        GetTransform().Translate(deltaX, deltaY);

        // Check for collisions with all other colliders in the scene
        for (const auto& actor : GetScene()->GetActors()) {
            if (actor != this) {
                BoxCollider2D* otherCollider = actor->GetComponent<BoxCollider2D>();
                if (otherCollider && mCollider->Intersects(otherCollider)) {
                    // Collision detected, revert to original position
                    GetTransform().SetPosition(originalX, originalY);
                    break;
                }
            }
        }
    }

private:
    BoxCollider2D* mCollider;
    float mSpeed;
};