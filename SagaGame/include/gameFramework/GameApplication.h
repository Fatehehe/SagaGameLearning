#pragma once

#include "framework/Application.h"

namespace saga{
    class PlayerShip;
    class GameApplication: public Application{
    public:
        GameApplication();
        void Tick(float deltaTime) override;

        void AddEnemyKill();
        int GetEnemyKillCount() const {return mEnemyKillCount;}

    private:
        weak<PlayerShip> playerShip;
        weak<World> mWorld;

        sf::Clock mEnemySpawnClock;
        float mSpawnInterval;
        void SpawnEnemy();

        int mEnemyKillCount = 0;
    };
}