#include "weapon/KineticProjectile.h"
#include "framework/Core.h"

namespace saga
{
    KineticProjectile::KineticProjectile(Actor* actor, float cooldownTime)
    : Projectile{actor},
    mCooldownClock{},
    mCooldownTime{cooldownTime}
    {

    }

    bool KineticProjectile::IsOnCooldown() const
    {
        if(mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime){
            return false;
        }
        return true;
    }

    void KineticProjectile::FireImpl()
    {
        mCooldownClock.restart();
        LOG("Kinetic projectile Fired!");
    }
} // namespace saga
