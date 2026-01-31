#pragma once

#include "framework/Actor.h"

namespace saga{
    class Projectile: public Actor{
    public:
        Projectile(World* world, Actor* owner, const std::string& texturePath, float speed = 200.f, float damage = 10.f);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);

        void Tick(float deltaTime) override;
        void OnOverlap(Actor* other)override;

    private:
        void Move(float deltaTime);
        Actor* mOwner;
        float mSpeed;
        float mDamage;
    };
}