#pragma once
#include "weapon/Projectile.h"
#include "SFML/System.hpp"

namespace saga{
    class KineticProjectile: public Projectile{
    public:
        KineticProjectile(Actor* actor, float cooldownTime);
        virtual bool IsOnCooldown() const override;
        // virtual bool CanFire() const override;
    private:
        virtual void FireImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
    };
}