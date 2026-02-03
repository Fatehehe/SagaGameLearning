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
    : Application{800,600, "Saga Window", sf::Style::Titlebar | sf::Style::Close},
    mSpawnInterval{1.5f}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());
        mWorld = LoadWorld<World>(); 
        playerShip = mWorld.lock()->SpawnActor<PlayerShip>();
        playerShip.lock()->SetActorLocation(sf::Vector2f{400.f, 300.f});
        playerShip.lock()->SetActorRotation(0.0f);
    }

    void GameApplication::Tick(float deltaTime)
    {
        if(mEnemySpawnClock.getElapsedTime().asSeconds() > mSpawnInterval){
            mEnemySpawnClock.restart();
            SpawnEnemy();
        }
    }

    void GameApplication::SpawnEnemy()
    {
        auto world = mWorld.lock();
        auto player = playerShip.lock();
        if(!world || !player) return;

        sf::Vector2u windowSize = GetWindowSize();
        int side = rand() % 4;
        sf::Vector2f spawnPos;

        switch(side){
            //Top
            case 0: spawnPos = {static_cast<float>(rand() % windowSize.x), -50.f}; break;
            //right
            case 1: spawnPos = {static_cast<float>(windowSize.x + 50.f), static_cast<float>(rand() % windowSize.y)}; break;
            //bottom
            case 2: spawnPos = {static_cast<float>(rand() % windowSize.x), static_cast<float>(windowSize.y + 50.f)}; break;
            //Left
            case 3: spawnPos = {-50.f, static_cast<float>(rand() % windowSize.y)}; break;
        }

        weak<EnemyShip> enemy = world->SpawnActor<EnemyShip>("PNG/Default/enemy_A.png");
        enemy.lock()->SetActorLocation(spawnPos);
        enemy.lock()->SetActorRotation(180.f);
        enemy.lock()->SetTarget(player.get());
    }
}