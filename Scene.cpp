#include "Scene.h"
#include "Assets.h"
#include <algorithm>
#include "Actor.h"
#include "BoxCollider2D.h"

Scene::Scene(const std::string& pTitle) {
	title = pTitle;
	mRenderer = nullptr;
	mUpdatingActors = false;
}

Scene::~Scene() {
    // Clean up all actors
    for (Actor* actor : mActors) {
        delete actor;
    }
    mActors.clear();

    for (Actor* actor : mPendingActors) {
        delete actor;
    }
    mPendingActors.clear();
}

void Scene::SetRenderer(Renderer* renderer) {
    this->mRenderer = renderer;
}

void Scene::Initialize() {
	// Base scene doesn't need to do anything
	// Derived scenes should implement their initialization
}

void Scene::Unload()
{
    //Free actors pointers memory
    //Because ~Actor() calls RemoveActor, we have to use a while loop
    while (!mActors.empty())
    {
        delete mActors.back();
    }
    //Free up resources
    Assets::Clear();
}


void Scene::Start() {
    // Start all existing actors
    for (Actor* actor : mActors) {
        actor->OnStart();
    }
}

void Scene::Update() {
    // Add any pending actors
    for (Actor* pending : mPendingActors) {
        pending->OnStart();
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // Update all actors
    mUpdatingActors = true;
    for (auto actor : mActors) {
        if (actor->GetState() == ActorState::Active) {
            actor->Update();
        }
    }
    mUpdatingActors = false;

    // Remove dead actors
    auto iter = std::remove_if(mActors.begin(), mActors.end(),
        [](Actor* actor) {
            if (actor->GetState() == ActorState::Dead) {
                delete actor;
                return true;
            }
            return false;
        });
    mActors.erase(iter, mActors.end());
}

//void Scene::Render() {
//    for (auto actor : mActors) {
//        BoxCollider2D* collider = actor->GetComponent<BoxCollider2D>();
//        if (collider) {
//            collider->Render(*mRenderer);
//        }
//    }
//}

void Scene::Render() {
    if (!mRenderer) {
        std::cout << "Error: Renderer is nullptr in Scene::Render()" << std::endl;
        return;
    }

    for (auto actor : mActors) {
        SpriteComponent* sprite = actor->GetComponent<SpriteComponent>();
        if (sprite) {
            sprite->Draw(*mRenderer);
        }

        BoxCollider2D* collider = actor->GetComponent<BoxCollider2D>();
        if (collider) {
            collider->Render(*mRenderer);
        }
    }
}

void Scene::OnInput(const SDL_Event& event) {
    // Base scene doesn't handle input
    // Derived scenes should implement their input handling
}

void Scene::Close() {
    for (Actor* actor : mActors) {
        actor->OnEnd();
    }

    for (Actor* actor : mActors) {
        delete actor;
    }
    mActors.clear();

    for (Actor* actor : mPendingActors) {
        delete actor;
    }
    mPendingActors.clear();
}

std::string Scene::GetTitle() const {
    return title;
}

void Scene::AddActor(Actor* actor) {
    // If updating actors, add to pending
    if (mUpdatingActors) {
        mPendingActors.emplace_back(actor);
    }
    else {
        mActors.emplace_back(actor);
        actor->OnStart();
    }
    actor->AttachScene(this);
}

void Scene::RemoveActor(Actor* actor) {
    // Is it in pending actors?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end()) {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
        delete actor;
        return;
    }

    // Is it in active actors?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
        actor->OnEnd();
        delete actor;
    }
}

void Scene::UpdateAllActors() {

	mUpdatingActors = true;

	// Update all existing actors
	for (Actor* actor : mActors) {
		actor->Update();
	}

	mUpdatingActors = false;

    // Add any pending Actors
	if (!mPendingActors.empty()) {
		mActors.insert(mActors.end(), mPendingActors.begin(), mPendingActors.end());
		mPendingActors.clear();
	}

    // Remove any actors marked for deletion
    auto it = std::remove_if(mActors.begin(), mActors.end(),
        [](Actor* actor) {
            return actor->GetState() == ActorState::Dead;  // Return true if actor should be removed
        });

    // Delete actors that were marked for removal
    for (auto i = it; i != mActors.end(); ++i) {
        delete* i;
    }

    // Actually remove them from the vector
    mActors.erase(it, mActors.end());

}
