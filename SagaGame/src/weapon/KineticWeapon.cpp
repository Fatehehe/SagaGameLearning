#include "weapon/KineticWeapon.h"
#include "framework/Core.h"

namespace saga
{
    KineticWeapon::KineticWeapon(Actor* actor, float cooldownTime)
    : Weapon{actor},
    mCooldownClock{},
    mCooldownTime{cooldownTime}
    {

    }

    bool KineticWeapon::IsOnCooldown() const
    {
        if(mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime){
            return false;
        }
        return true;
    }

    void KineticWeapon::FireImpl()
    {
        mCooldownClock.restart();
        LOG("Kinetic projectile Fired!");
    }
} // namespace saga
