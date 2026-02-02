#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerShip.h"
#include "enemies/EnemyShip.h"
#include "framework/AssetManager.h"
#include "config.h"

namespace saga{
    Application *GetApplication()
    {
        return new GameApplication();
    }

    GameApplication::GameApplication()
    : Application{800,600, "Saga Window", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());
        weak<World> newWorld = LoadWorld<World>(); 
        testShip = newWorld.lock()->SpawnActor<PlayerShip>();
        testShip.lock()->SetActorLocation(sf::Vector2f{400.f, 300.f});
        testShip.lock()->SetActorRotation(0.0f);

        weak<EnemyShip> enemy = newWorld.lock()->SpawnActor<EnemyShip>("PNG/Default/enemy_A.png");
        enemy.lock()->SetActorLocation(sf::Vector2f(400.f, 150.f));
        enemy.lock()->SetActorRotation(180.f);
    }

    void GameApplication::Tick(float deltaTime)
    {

    }
    
}