#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace saga{
    Application *GetApplication()
    {
        return new GameApplication();
    }

    GameApplication::GameApplication()
    : Application{800,600, "Saga Window", sf::Style::Titlebar | sf::Style::Close}
    {
        weak<World> newWorld = LoadWorld<World>(); 
        actor_Test = newWorld.lock()->SpawnActor<Actor>();
        actor_Test.lock()->SetTexturePath("/Users/fatakhillahkhaqo/Documents/Learnings/CPP/SagaGame/SagaGame/assets/PNG/Default/ship_F.png");
        timer = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        timer += deltaTime;
        // LOG("Time: %f", timer );
        if(timer > 2.f){
            if(!actor_Test.expired()){
                actor_Test.lock()->Destroy();
            }
        }
    }
    
}