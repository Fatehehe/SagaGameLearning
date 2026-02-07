#pragma once
#include <SFML/System.hpp>

namespace saga
{
    class Actor;
    class Weapon {
    public:
        void Fire();
        virtual bool CanFire() const {return true;}
        virtual bool IsOnCooldown() const;
        Actor* GetOwner() const {return mOwner;}

    protected:
        Weapon(Actor* actor);
        virtual void FireImpl() = 0;
        sf::Clock mCooldownClock;
        float mCooldownTime = 0.5f;

    private:
        Actor* mOwner;
    };
} // namespace saga
