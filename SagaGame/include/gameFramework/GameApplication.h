#pragma once

#include "framework/Application.h"

namespace saga{
    class PlayerShip;
    class GameApplication: public Application{
    public:
        GameApplication();
        virtual void Tick(float deltaTime) override;
    private:
        float timer;
        weak<PlayerShip> testShip;
    };
}