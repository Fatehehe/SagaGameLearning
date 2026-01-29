#include "weapon/Projectile.h"

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
    }

    void Projectile::Move(float deltaTime)
    {
        float rotationDegrees = GetActorRotation();
        float rotationRadians = rotationDegrees * (3.14159265f/180.f);
        sf::Vector2f forward(std::cos(rotationRadians), std::sin(rotationRadians));

        AddActorLocationOffset(forward * mSpeed * deltaTime);
    }
}
