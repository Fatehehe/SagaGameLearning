#include "enemies/EnemyShip.h"
#include "framework/Core.h"

namespace saga{
    EnemyShip::EnemyShip(World *world, const std::string &texturePath)
    : Ship(world, texturePath)
    {
    }

    void EnemyShip::Tick(float deltaTime)
    {
        Ship::Tick(deltaTime);
        //Add anime AI behavior
    }
    void EnemyShip::OnOverlap(Actor *other)
    {
        if(other == this) return;
        LOG("Enemy hit by: %s", typeid(*other).name());
        Destroy();
    }
};