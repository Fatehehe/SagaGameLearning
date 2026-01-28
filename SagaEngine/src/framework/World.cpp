#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
// #include "World.h"

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
                iter->get()->TickInternal(deltaTime);
                ++iter;
            }
        }
        
        Tick(deltaTime);
    }

    void World::Render(sf::RenderWindow &renderWindow)
    {
        for(auto& actor : mActors){
            actor->Render(renderWindow);
        }
    }

    World::~World()
    {
    }

    sf::Vector2u World::GetWindowSize() const {
        return mOwnerApp->GetWindowSize();
    } 

    void World::BeginPlay()
    {
    }

    void World::Tick(float deltaTime)
    {
    }

}
