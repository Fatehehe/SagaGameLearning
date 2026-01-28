#pragma once

#include "framework/Actor.h"

namespace saga{
    class Projectile: public Actor{
    public:
        Projectile(World* world, Actor* owner, const std::string& texturePath, float speed, float damage);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);

    private:
        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
}