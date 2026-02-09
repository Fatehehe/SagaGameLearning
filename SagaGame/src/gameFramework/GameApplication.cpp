#include <iostream>
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
    mSpawnInterval{1.5f},
    mKillCountText{mFont}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());

        if(!mFont.openFromFile(GetResourceDirectory() + "Fonts/Kenney Future.ttf")){
            std::cerr << "Failed to load font" << std::endl;
        }

        mKillCountText.setFont(mFont);
        mKillCountText.setCharacterSize(18);
        mKillCountText.setFillColor(sf::Color::White);
        mKillCountText.setPosition(sf::Vector2f{10.f,10.f});
        mKillCountText.setString("Kills: 0");

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

    void GameApplication::Render(sf::RenderWindow &window){
        Application::Render(window);
        window.draw(mKillCountText);
    }

    void GameApplication::AddEnemyKill()
    {
        ++mEnemyKillCount;
        // LOG("Enemy kill count: %d", mEnemyKillCount);
        mKillCountText.setString("Kills: " + std::to_string(mEnemyKillCount));

        if(!playerShip.expired()){
            auto player = playerShip.lock();
            if(mEnemyKillCount == 10){
                player->UpgradeToSpreadShot();
            }
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