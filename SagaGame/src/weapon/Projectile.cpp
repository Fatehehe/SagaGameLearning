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
}