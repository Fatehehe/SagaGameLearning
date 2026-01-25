#include "framework/World.h"
#include "framework/Core.h"

namespace saga{
    World::World(Application* ownerApp)
    : mOwnerApp{ownerApp},
    mHasBegunPlay{false}
    {
         
    }

    void World::BeginPlayInternal()
    {
        if(!mHasBegunPlay){
            mHasBegunPlay = true;
            LOG("WORLD BEGIN PLAY!");
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        LOG("WORLD TICK");
        Tick(deltaTime);
    }

    World::~World()
    {
    }

    void World::BeginPlay()
    {
    }

    void World::Tick(float deltaTime)
    {
    }

}
