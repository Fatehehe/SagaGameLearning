#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace saga{
    GameApplication::GameApplication()
    {
        weak<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
    }

    Application* GetApplication(){
        return new GameApplication(); 
    }
}