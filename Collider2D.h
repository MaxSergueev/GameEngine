#pragma once
#include "Component.h"
#include "Transform2D.h"
#include "Actor.h"
#include "Vec2.h"

class Collider2D : public Component {
public:
    Collider2D(Actor& owner, int updateOrder = 200)
        : Component(owner, updateOrder)
        , mIsTrigger(false)
        , mOffset(0.0f, 0.0f)
    {
    }

    virtual ~Collider2D() = default;

    // Pure virtual function for collision checks
    virtual bool Intersects(const Collider2D* other) const = 0;

    // Getters/Setters
    bool IsTrigger() const { return mIsTrigger; }
    void SetTrigger(bool isTrigger) { mIsTrigger = isTrigger; }

    void SetOffset(float x, float y) { mOffset = Vector2(x, y); }
    Vector2 GetOffset() const { return mOffset; }

    // Get world position
    Vector2 GetWorldPosition() const {
        float x, y;
        mOwner.GetTransform().GetPosition(x, y);
        return Vector2(x + mOffset.x, y + mOffset.y);
    }
protected:

    bool mIsTrigger;  // If true, this collider is a trigger (no physical collision)
    Vector2 mOffset;  // Offset from the transform's position
};