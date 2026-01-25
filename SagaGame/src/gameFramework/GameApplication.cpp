#include "gameFramework/GameApplication.h"
#include "framework/World.h"

namespace saga{
    GameApplication::GameApplication()
    {
        LoadWorld<World>();
    }

    Application* GetApplication(){
        return new GameApplication(); 
    }
}