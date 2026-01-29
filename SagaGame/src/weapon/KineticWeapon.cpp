#include "weapon/KineticWeapon.h"
#include "framework/Core.h"
#include "weapon/Projectile.h"
#include "framework/World.h"

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
        weak<Projectile> nweProjectile = GetOwner()->GetWorld()->SpawnActor<Projectile>(GetOwner(), "PNG/Default/effect_yellow.png");
        nweProjectile.lock()->SetActorLocation(GetOwner()->GetActorLocation());
        nweProjectile.lock()->SetActorRotation(GetOwner()->GetActorRotation());
    }
} // namespace saga
