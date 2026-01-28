#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

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
        template<typename ActorType>
        weak<ActorType> SpawnActor();

        sf::Vector2u GetWindowSize() const;

    private:

        Application* mOwnerApp;
        bool mHasBegunPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPengingActors;
    };

    template <typename ActorType>
    weak<ActorType> World::SpawnActor()
    {
        shared<ActorType> newActor { new ActorType(this) };
        mPengingActors.push_back(newActor);
        return newActor;
    }
}