#pragma once

#include "framework/Actor.h"

namespace saga{
    class Projectile: public Actor{
    public:
        Projectile(World* world, Actor* owner, const std::string& texturePath, float speed = 200.f, float damage = 10.f);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);

        virtual void Tick(float deltaTime) override;

    private:
        void Move(float deltaTime);
        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
}