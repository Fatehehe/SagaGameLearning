#include "enemies/EnemyShip.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace saga{
    EnemyShip::EnemyShip(World *world, const std::string &texturePath)
    : Ship(world, texturePath),
    mHealth{50.f},
    mTarget{nullptr},
    mSpeed{150.f}
    {
          mWeapon = std::make_unique<KineticWeapon>(this, mFireCooldown);
    }

    void EnemyShip::Tick(float deltaTime)
    {
        Ship::Tick(deltaTime);
        if(!mTarget) return;

        if(mTarget){
            sf::Vector2f toTarget = mTarget->GetActorLocation() - GetActorLocation();

            if(toTarget != sf::Vector2f{0.f,0.f}){
                float angleRad = std::atan2(toTarget.y, toTarget.x);
                float angelDeg = sf::radians(angleRad).asDegrees();
                SetActorRotation(angelDeg + 90.f);
            }

            if(mWeapon){
                mWeapon->Fire();
            }
        }
        
        //Add anime AI behavior
        sf::Vector2f toPlayer = mTarget->GetActorLocation() - GetActorLocation();
        if(toPlayer != sf::Vector2f(0.f,0.f)){
            toPlayer = toPlayer.normalized();
        }

        sf::Vector2f movement = toPlayer * mSpeed * deltaTime;  
        AddActorLocationOffset(movement);
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

    void EnemyShip::SetTarget(Actor *target)
    {
        mTarget = target;
    }
};

