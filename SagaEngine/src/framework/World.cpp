#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace saga{
    World::World(Application* ownerApp)
    : mOwnerApp{ownerApp},
    mHasBegunPlay{false},
    mActors{},
    mPengingActors{}
    {
         
    }

    void World::BeginPlayInternal()
    {
        if(!mHasBegunPlay){
            mHasBegunPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        for(shared<Actor> actor : mPengingActors){
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }

        mPengingActors.clear();

        for(auto iter = mActors.begin(); iter != mActors.end();){
            if(iter->get()->IsPendingDestroy()){
                iter = mActors.erase(iter);
            }else{
                iter->get()->Tick(deltaTime);
                ++iter;
            }
        }
        
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
