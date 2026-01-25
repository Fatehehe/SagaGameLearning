#pragma once

#include "framework/Core.h"
#include "framework/Object.h"

namespace saga{
    class World;
    class Actor: public Object{
    public:
        Actor(World* ownerWorld);
        virtual ~Actor();

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
    
    private:
        World* mOwnerWorld;
        bool mHasBegunPlay;
    };
}