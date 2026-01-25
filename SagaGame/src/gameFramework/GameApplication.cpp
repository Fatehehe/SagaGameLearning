#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace saga{
    Application *GetApplication()
    {
        return new GameApplication();
    }

    GameApplication::GameApplication()
    {
        weak<World> newWorld = LoadWorld<World>();
        // newWorld.lock()->SpawnActor<Actor>();
        actor_Test = newWorld.lock()->SpawnActor<Actor>();
        timer = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        timer += deltaTime;
        LOG("Time: %f", timer );
        if(timer > 2.f){
            if(!actor_Test.expired()){
                actor_Test.lock()->Destroy();
            }
        }
    }
    
}