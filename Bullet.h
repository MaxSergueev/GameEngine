#pragma once
#include "Actor.h"
#include "BoxCollider2D.h"
#include "Scene.h"
#include "Time.h"
class Bullet : public Actor {
public:
    Bullet(Scene* scene, Actor* shooter, bool movingUp)
        : Actor(scene)
        , mShooter(shooter)
        , mSpeed(400.0f)
        , mMovingUp(movingUp)
    {
        mCollider = AddComponent<BoxCollider2D>();
        mCollider->SetSize(5.0f, 15.0f);
    }

    void OnUpdate() override {
        // Move bullet
        float posX, posY;
        GetTransform().GetPosition(posX, posY);
        float deltaY = mMovingUp ? -mSpeed * Time::deltaTime : mSpeed * Time::deltaTime;
        GetTransform().Translate(0.0f, deltaY);

        // Check for collisions
        for (const auto& actor : GetScene()->GetActors()) {
            if (actor != this && actor != mShooter) {
                BoxCollider2D* otherCollider = actor->GetComponent<BoxCollider2D>();
                if (otherCollider && mCollider->Intersects(otherCollider)) {
                    actor->Destroy();  // Destroy hit actor
                    Destroy();         // Destroy bullet
                    break;
                }
            }
        }

        // Destroy if off screen
        GetTransform().GetPosition(posX, posY);
        if (posY < 0 || posY > 800) { 
            Destroy();
        }
    }

private:
    BoxCollider2D* mCollider;
    Actor* mShooter;
    float mSpeed;
    bool mMovingUp;
};