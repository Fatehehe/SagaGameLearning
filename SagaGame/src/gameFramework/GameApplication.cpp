#include "gameFramework/GameApplication.h"

namespace saga{
    GameApplication::GameApplication()
    {

    }

    Application* GetApplication(){
        return new GameApplication();
    }
}