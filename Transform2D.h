#pragma once
#include "Component.h"
#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592
#endif

class Transform2D : public Component {
public:
    Transform2D(Actor& owner, int updateOrder = 100)
        : Component(owner, updateOrder)
        , positionX(0.0f)
        , positionY(0.0f)
        , scaleX(1.0f)
        , scaleY(1.0f)
        , rotation(0.0f)
    {
    }

    // Required Component interface
    void OnStart() override {}
    void Update() override {}
    void OnEnd() override {}

    // Position setters and getters
    void SetPosition(float x, float y) {
        positionX = x;
        positionY = y;
    }

    void GetPosition(float& x, float& y) const {
        x = positionX;
        y = positionY;
    }

    // Scale setters and getters
    void SetScale(float x, float y) {
        scaleX = x;
        scaleY = y;
    }

    void GetScale(float& x, float& y) const {
        x = scaleX;
        y = scaleY;
    }

    // Rotation setters and getters (in radians)
    void SetRotation(float rot) {
        rotation = rot;
    }

    float GetRotation() const {
        return rotation;
    }

    // Utility functions
    void SetRotationDegrees(float degrees) {
        rotation = degrees * M_PI / 180.0f;
    }

    float GetRotationDegrees() const {
        return rotation * 180.0f / M_PI;
    }

    // Transform manipulation
    void Translate(float dx, float dy) {
        positionX += dx;
        positionY += dy;
    }

    void Scale(float sx, float sy) {
        scaleX *= sx;
        scaleY *= sy;
    }

    void Rotate(float angle) {
        rotation += angle;
    }

    // Transform point from local space to world space
    void TransformPoint(float& x, float& y) const {
        // Apply scale
        x *= scaleX;
        y *= scaleY;

        // Apply rotation
        float cosRot = cos(rotation);
        float sinRot = sin(rotation);
        float tempX = x * cosRot - y * sinRot;
        float tempY = x * sinRot + y * cosRot;
        x = tempX;
        y = tempY;

        // Apply translation
        x += positionX;
        y += positionY;
    }

    // Reset transform to default values
    void Reset() {
        positionX = positionY = 0.0f;
        scaleX = scaleY = 1.0f;
        rotation = 0.0f;
    }

private:
    float positionX;
    float positionY;
    float scaleX;
    float scaleY;
    float rotation;
};