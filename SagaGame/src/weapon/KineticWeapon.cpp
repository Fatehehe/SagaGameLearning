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

        weak<Projectile> newProjectile = world->SpawnActor<Projectile>(owner, "PNG/Default/star_tiny.png");
        newProjectile.lock()->SetActorLocation(owner->GetActorLocation());
        newProjectile.lock()->SetActorRotation(rotation);

        if(auto ship = dynamic_cast<Ship*>(owner)){
            newProjectile.lock()->SetDamage(ship->GetProjectileDamage());
        }else{
            newProjectile.lock()->SetDamage(10.f);
        }

        if(dynamic_cast<PlayerShip*>(owner)){
            newProjectile.lock()->SetProjectileType(ProjectileType::Player);
        }else{
            newProjectile.lock()->SetProjectileType(ProjectileType::Enemy);
        }
    }
} // namespace saga
