#include "framework/Actor.h"

namespace saga{
    Actor::Actor(World *ownerWorld)
    : mOwnerWorld{ownerWorld}, 
    mHasBegunPlay{false}
    {

    }

    void Actor::BeginPlayInternal()
    {
        mHasBegunPlay = true;
        BeginPlay();
    }

    void Actor::TickInternal(float deltaTime)
    {
    }

    void Actor::BeginPlay()
    {
        LOG("ACTOR BEGIN PLAY");
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("ACTOR BEGIN TICK");
    }
}