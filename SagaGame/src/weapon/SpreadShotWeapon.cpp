#include "weapon/SpreadShotWeapon.h"
#include "weapon/Projectile.h"
#include "framework/Actor.h"
#include "player/PlayerShip.h"
#include "framework/World.h"

namespace saga{
    SpreadShotWeapon::SpreadShotWeapon(Actor *owner, float cooldownTime, int numProjectiles, float spreadAngle)
    : KineticWeapon{owner, cooldownTime},
    mNumProjectiles{numProjectiles},
    mSpreadAngle{spreadAngle}
    {
        mCooldownTime = cooldownTime;
    }
    
    void SpreadShotWeapon::FireImpl()
    {
        mCooldownClock.restart();

        auto owner = GetOwner();
        auto world = owner->GetWorld();
        auto ship = dynamic_cast<PlayerShip*>(owner);
        if(!world || !ship) return;

        float baseAngle = owner->GetActorRotation();

        if(auto player = dynamic_cast<PlayerShip*>(owner)){
            baseAngle = player->GetAimAngle();
        }

        float halfsSpread = mSpreadAngle/2;

        for(int i = 0; i < mNumProjectiles; i++){
            float angleOffset = (mNumProjectiles == 1) ? 0.f : (float(i) / float(mNumProjectiles - 1))  * mSpreadAngle - halfsSpread;
            float rotation = baseAngle + angleOffset;

            auto projectile = world->SpawnActor<Projectile>(owner, "PNG/Default/star_tiny.png");
            projectile.lock()->SetActorLocation(owner->GetActorLocation());
            projectile.lock()->SetActorRotation(rotation);
            projectile.lock()->SetDamage(ship->GetProjectileDamage());

            projectile.lock()->SetProjectileType(dynamic_cast<PlayerShip*>(owner) ? ProjectileType::Player : ProjectileType::Enemy);
        }
    }
}

