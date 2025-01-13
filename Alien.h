#pragma once
#include "Actor.h"
#include "BoxCollider2D.h"
#include "Scene.h"
#include "Bullet.h"
#include "SpacePlayer.h"
class Alien : public Actor {
public:
    Alien(Scene* scene)
        : Actor(scene)
        , mShootCooldown(0.0f)
        , mMoveSpeed(100.0f)
        , mMovingRight(true)
        , mDescendAmount(60.0f)
    {
        mCollider = AddComponent<BoxCollider2D>();
        mCollider->SetSize(40.0f, 40.0f);
    }

    void OnUpdate() override {
        // Movement
        float posX, posY;
        GetTransform().GetPosition(posX, posY);

        // Move horizontally
        float deltaX = mMovingRight ? mMoveSpeed * Time::deltaTime : -mMoveSpeed * Time::deltaTime;
        GetTransform().Translate(deltaX, 0.0f);

        // Check screen bounds
        GetTransform().GetPosition(posX, posY);
        if (mMovingRight && posX > 750.0f) {
            // Hit right edge, move down and change direction
            mMovingRight = false;
            GetTransform().Translate(0.0f, mDescendAmount);
        }
        else if (!mMovingRight && posX < 50.0f) {
            // Hit left edge, move down and change direction
            mMovingRight = true;
            GetTransform().Translate(0.0f, mDescendAmount);
        }

        // Shooting logic
        mShootCooldown -= 0.016f;
        if (mShootCooldown <= 0.0f) {
            // Find player (Not actually doing anything with this yet)
            for (const auto& actor : GetScene()->GetActors()) {
                SpacePlayer* player = dynamic_cast<SpacePlayer*>(actor);
                if (player) {
                    float playerX, playerY;
                    player->GetTransform().GetPosition(playerX, playerY);

                    // Shoot
                    if (rand() % 100 < 1) { 
                        Bullet* bullet = new Bullet(GetScene(), this, false);
                        bullet->GetTransform().SetPosition(posX, posY + 20.0f);
                        GetScene()->AddActor(bullet);
                        mShootCooldown = 2.0f;
                    }
                    break;
                }
            }
        }
    }

private:
    BoxCollider2D* mCollider;
    float mShootCooldown;
    float mMoveSpeed;
    bool mMovingRight;
    float mDescendAmount;
};