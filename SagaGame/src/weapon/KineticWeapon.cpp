#include "weapon/KineticWeapon.h"
#include "framework/World.h"
#include "framework/Core.h"
#include "weapon/Projectile.h"
#include "player/PlayerShip.h"

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

        auto owner = GetOwner();
        auto world = owner->GetWorld();
        auto player = dynamic_cast<PlayerShip*>(owner);

        float rotation = owner->GetActorRotation();
        if(player){
            rotation = player->GetAimAngle();
        }

        weak<Projectile> nweProjectile = world->SpawnActor<Projectile>(owner, "PNG/Default/star_tiny.png");
        nweProjectile.lock()->SetActorLocation(owner->GetActorLocation());
        nweProjectile.lock()->SetActorRotation(rotation);
        nweProjectile.lock()->SetDamage(10.f);
    }
} // namespace saga
