#pragma once

#include "framework/Core.h"

namespace saga{
    class World;
    class Actor{
    public:
        Actor(World* ownerWorld);

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
    
    private:
        World* mOwnerWorld;
        bool mHasBegunPlay;
    };
}