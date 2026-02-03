#pragma once

#include "framework/Application.h"

namespace saga{
    class PlayerShip;
    class GameApplication: public Application{
    public:
        GameApplication();
        virtual void Tick(float deltaTime) override;
    private:
        weak<PlayerShip> playerShip;
        weak<World> mWorld;

        sf::Clock mEnemySpawnClock;
        float mSpawnInterval;
        void SpawnEnemy();
    };
}