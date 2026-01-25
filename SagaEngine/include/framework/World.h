#pragma once

namespace saga{
    class Application;
    class World{
    public:
        explicit World(Application* ownerApp);

        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        
        void BeginPlayInternal();
        void TickInternal(float deltaTime);

        virtual ~World();
    private:

        Application* mOwnerApp;
        bool mHasBegunPlay;
    };
}