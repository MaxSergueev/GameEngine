#pragma once
#include "Collider2D.h"
#include "Renderer.h"

class BoxCollider2D : public Collider2D {
public:
    BoxCollider2D(Actor& owner, int updateOrder = 200)
        : Collider2D(owner, updateOrder)
        , mWidth(100.0f)
        , mHeight(100.0f)
    {
    }

    void OnStart() override {}
    void Update() override {}
    void OnEnd() override {}

    bool Intersects(const Collider2D* other) const override {
        const BoxCollider2D* boxOther = dynamic_cast<const BoxCollider2D*>(other);
        if (!boxOther) return false;

        Vector2 pos = GetWorldPosition();
        Vector2 otherPos = boxOther->GetWorldPosition();

        float left = pos.x - (mWidth / 2.0f);
        float right = pos.x + (mWidth / 2.0f);
        float top = pos.y - (mHeight / 2.0f);
        float bottom = pos.y + (mHeight / 2.0f);

        float otherLeft = otherPos.x - (boxOther->GetWidth() / 2.0f);
        float otherRight = otherPos.x + (boxOther->GetWidth() / 2.0f);
        float otherTop = otherPos.y - (boxOther->GetHeight() / 2.0f);
        float otherBottom = otherPos.y + (boxOther->GetHeight() / 2.0f);

        return (right >= otherLeft && left <= otherRight &&
            bottom >= otherTop && top <= otherBottom);
    }

    void GetCorners(Vector2 corners[4]) const {
        Vector2 center = GetWorldPosition();
        float halfWidth = mWidth / 2.0f;
        float halfHeight = mHeight / 2.0f;

        corners[0] = Vector2(center.x - halfWidth, center.y - halfHeight);
        corners[1] = Vector2(center.x + halfWidth, center.y - halfHeight);
        corners[2] = Vector2(center.x - halfWidth, center.y + halfHeight);
        corners[3] = Vector2(center.x + halfWidth, center.y + halfHeight);
    }

    float GetWidth() const { return mWidth; }
    float GetHeight() const { return mHeight; }

    void SetWidth(float width) { mWidth = width; }
    void SetHeight(float height) { mHeight = height; }
    void SetSize(float width, float height) {
        mWidth = width;
        mHeight = height;
    }

    void Render(Renderer& renderer) const override {
        Vector2 pos = GetWorldPosition();
        Rectangle rect = { pos, Vector2(mWidth, mHeight) };
        renderer.DrawRect(rect);
    }

private:
    float mWidth;
    float mHeight;
};