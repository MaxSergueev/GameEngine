#pragma once

class Actor;

class Component
{
public:
    Component() = delete;

    Component(Actor& owner, int updateOrder = 100)
        : mOwner(owner), mUpdateOrder(updateOrder), mIsActive(true) {
    }

    virtual ~Component() {}

    virtual void OnStart() = 0;

    virtual void Update() {}
    virtual void Render(Renderer& renderer) const {}
    virtual void OnEnd() {}

    bool IsActive() const { return mIsActive; }
    int GetUpdateOrder() const { return mUpdateOrder; }

    void SetActive(bool isActive) { mIsActive = isActive; }

protected:
    bool mIsActive;
    Actor& mOwner;
    int mUpdateOrder;
};