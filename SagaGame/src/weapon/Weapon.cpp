#include "weapon/Weapon.h"

namespace saga{
    
    Weapon::Weapon(Actor* owner)
    : mOwner{owner},
    mCooldownTime{0.5f}
    {
    
    }

    void Weapon::Fire(){
        if(CanFire() && !IsOnCooldown()){
            FireImpl();
        }
    }
    
    bool Weapon::IsOnCooldown() const
    {
        return mCooldownClock.getElapsedTime().asSeconds() < mCooldownTime;
    }
}

