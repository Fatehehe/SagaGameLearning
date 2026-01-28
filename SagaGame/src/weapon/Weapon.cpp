#include "weapon/Weapon.h"

namespace saga{
    void Weapon::Fire(){
        if(CanFire() && !IsOnCooldown()){
            FireImpl();
        }
    }

    Weapon::Weapon(Actor* owner)
    : mOwner{owner}
    {

    }
}