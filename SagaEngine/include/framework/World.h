#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include "framework/PhysicsSystem.h"

namespace saga{
    class Actor;
    class Application;
    class World{
    public:
        explicit World(Application* ownerApp);

        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        
        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        void Render(sf::RenderWindow& renderWindow);

        virtual ~World();

        template<typename ActorType, typename... Args>
        weak<ActorType> SpawnActor(Args... args);

        sf::Vector2u GetWindowSize() const;
        sf::RenderWindow& GetRenderWindow() const;

        void CleanCycle();

        std::vector<Actor*> mActorsToRemoveImmediately;
        void QueueActorForImmediateRemoval(Actor* actor);
        void RemoveActorImmediately(Actor* actor);

    private:

        Application* mOwnerApp;
        bool mHasBegunPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPengingActors;

        PhysicsSystem mPhysicsSystem;
    };

    template <typename ActorType, typename... Args>
    weak<ActorType> World::SpawnActor(Args... args )
    {
        shared<ActorType> newActor { new ActorType(this, args...) };
        mPengingActors.push_back(newActor);
        return newActor;
    }
}