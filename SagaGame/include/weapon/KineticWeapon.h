#pragma once
#include "weapon/Weapon.h"
#include "SFML/System.hpp"

namespace saga{
    class KineticWeapon: public Weapon{
    public:
        KineticWeapon(Actor* actor, float cooldownTime);
        bool IsOnCooldown() const override;
        // virtual bool CanFire() const override;
    private:
        void FireImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;
    };
}