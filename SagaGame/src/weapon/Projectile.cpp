#include "weapon/Projectile.h"
#include "enemies/EnemyShip.h"
#include "framework/World.h"

namespace saga{
    Projectile::Projectile(World *world, Actor *owner, const std::string &texturePath, float speed, float damage)
    : Actor{world, texturePath},
    mOwner{owner},
    mSpeed{speed},
    mDamage{damage}
    {

    }

    void Projectile::SetSpeed(float newSpeed)
    {
        mSpeed = newSpeed;
    }

    void Projectile::SetDamage(float newDamage)
    {
        mDamage = newDamage;
    }

    void Projectile::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
        if(IsActorOutOfBound()){
            Destroy();
        } 
    }

    void Projectile::OnOverlap(Actor *other)
    {
        if(other == mOwner) return;
        if(auto enemy = dynamic_cast<EnemyShip*>(other)){
            // GetWorld()->QueueActorForImmediateRemoval(other);
            enemy->ApplyDamage(mDamage);
            GetWorld()->QueueActorForImmediateRemoval(this);
        }
    }

    void Projectile::Move(float deltaTime)
    {
        float rotationDegrees = GetActorRotation();
        float rotationRadians = rotationDegrees * (3.14159265f/180.f);
        sf::Vector2f forward(std::sin(rotationRadians), -std::cos(rotationRadians));

        AddActorLocationOffset(forward * mSpeed * deltaTime);
    }
}
