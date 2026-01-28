#include "weapon/Projectile.h"

namespace saga{
    void Projectile::Fire(){
        if(CanFire() && !IsOnCooldown()){
            FireImpl();
        }
    }

    Projectile::Projectile(Actor* owner)
    : mOwner{owner}
    {

    }
}