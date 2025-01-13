#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Component.h"
#include "Transform2D.h"

class Scene;

enum class ActorState {
    Active,
    Paused,
    Dead
};

class Actor {
public:
    Actor(Scene* scene = nullptr)
        : mScene(scene)
        , mState(ActorState::Active)
        , mTransform(*this)
    {
        mComponents.push_back(&mTransform);
    }

    virtual ~Actor() {
        mComponents.erase(mComponents.begin() + 1, mComponents.end());
    }

    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;

    virtual void OnStart() {
        for (auto component : mComponents) {
            component->OnStart();
        }
    }

    void Update() {
        if (mState == ActorState::Active) {
            UpdateComponents();
            OnUpdate();
        }
    }

    virtual void OnUpdate() {}

    virtual void OnEnd() {
        for (auto component : mComponents) {
            component->OnEnd();
        }
    }

    void AttachScene(Scene* scene) {
        mScene = scene;
    }

    template<typename T>
    T* AddComponent(int updateOrder = 100) {
        T* component = new T(*this, updateOrder);

        auto iter = std::upper_bound(mComponents.begin(), mComponents.end(),
            component,
            [](Component* a, Component* b) {
                return a->GetUpdateOrder() < b->GetUpdateOrder();
            });

        mComponents.insert(iter, component);
        return component;
    }

    void RemoveComponent(Component* component) {
        auto iter = std::find(mComponents.begin(), mComponents.end(), component);
        if (iter != mComponents.end()) {
            (*iter)->OnEnd();
            delete* iter;
            mComponents.erase(iter);
        }
    }

    void SetActive(bool isActive) {
        mState = isActive ? ActorState::Active : ActorState::Paused;
        for (auto component : mComponents) {
            component->SetActive(isActive);
        }
    }

    void Destroy() {
        mState = ActorState::Dead;
    }

    Scene* GetScene() const { return mScene; }
    Transform2D& GetTransform() { return mTransform; }
    ActorState GetState() const { return mState; }
    const std::vector<Component*>& GetComponents() const { return mComponents; }

    template<typename T>
    T* GetComponent() {
        for (auto component : mComponents) {
            T* result = dynamic_cast<T*>(component);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

protected:
    void UpdateComponents() {
        for (auto component : mComponents) {
            if (component->IsActive()) {
                component->Update();
            }
        }
    }

private:
    Scene* mScene;
    ActorState mState;
    Transform2D mTransform;
    std::vector<Component*> mComponents;
};