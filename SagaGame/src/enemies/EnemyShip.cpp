#include "enemies/EnemyShip.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace saga{
    EnemyShip::EnemyShip(World *world, const std::string &texturePath)
    : Ship(world, texturePath),
    mHealth{50.f}
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
    }

    void EnemyShip::ApplyDamage(float amount)
    {
        mHealth.ApplyDamage(amount);
        if(mHealth.IsDead()){
            GetWorld()->QueueActorForImmediateRemoval(this);
        }else{
            LOG("Enemy took %f damage, remaining health is %f", amount, mHealth.GetHealth());
        }
    }
};

