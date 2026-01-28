#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "ship/Ship.h"
#include "config.h"

namespace saga{
    Application *GetApplication()
    {
        return new GameApplication();
    }

    GameApplication::GameApplication()
    : Application{800,600, "Saga Window", sf::Style::Titlebar | sf::Style::Close}
    {
        weak<World> newWorld = LoadWorld<World>(); 
        testShip = newWorld.lock()->SpawnActor<Ship>();
        testShip.lock()->SetTexturePath(GetResourceDirectory() + "PNG/Default/ship_F.png");
        testShip.lock()->SetActorLocation(sf::Vector2f{400.f, 300.f});
        testShip.lock()->SetActorRotation(0.0f);
        testShip.lock()->SetVelocity(sf::Vector2f{0.0f, -200.0f});
        timer = 0;
    }

    void GameApplication::Tick(float deltaTime)
    {
        // timer += deltaTime;
        // // LOG("Time: %f", timer );
        // if(timer > 2.f){
        //     if(!actor_Test.expired()){
        //         actor_Test.lock()->Destroy();
        //     }
        // }
    }
    
}