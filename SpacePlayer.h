#pragma once
#include "Actor.h"
#include "BoxCollider2D.h"
#include "Scene.h"
#include "Bullet.h"
class SpacePlayer : public Actor {
public:
    SpacePlayer(Scene* scene) : Actor(scene), mSpeed(300.0f), mShootCooldown(0.0f) {
        mCollider = AddComponent<BoxCollider2D>();
        mCollider->SetSize(50.0f, 30.0f);

        // Position at bottom of screen
        GetTransform().SetPosition(400.0f, 750.0f);  
    }

    void OnUpdate() override {
        float posX, posY;
        GetTransform().GetPosition(posX, posY);

        // Only move on X axis
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
        float deltaX = 0.0f;

        if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
            deltaX -= mSpeed * 0.016f;
        }
        if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
            deltaX += mSpeed * 0.016f;
        }

        // Clamp to screen bounds
        float newX = posX + deltaX;
        if (newX < 25.0f) newX = 25.0f;
        if (newX > 775.0f) newX = 775.0f;

        GetTransform().SetPosition(newX, posY);

        // Shooting
        mShootCooldown -= 0.016f;
        if (mShootCooldown <= 0.0f && keyState[SDL_SCANCODE_SPACE]) {
            Bullet* bullet = new Bullet(GetScene(), this, true);
            bullet->GetTransform().SetPosition(posX, posY - 20.0f);
            GetScene()->AddActor(bullet);
            mShootCooldown = 0.5f;
        }
    }

private:
    BoxCollider2D* mCollider;
    float mSpeed;
    float mShootCooldown;
};