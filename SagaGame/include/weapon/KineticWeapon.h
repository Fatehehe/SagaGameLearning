#pragma once
#include "weapon/Weapon.h"
#include "SFML/System.hpp"

namespace saga{
    class KineticWeapon: public Weapon{
    public:
        KineticWeapon(Actor* actor, float cooldownTime);
        virtual bool IsOnCooldown() const override;
        // virtual bool CanFire() const override;
    private:
        virtual void FireImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
    };
}