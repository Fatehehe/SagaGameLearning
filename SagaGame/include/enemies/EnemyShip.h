#pragma once

#include "ship/Ship.h"
#include "components/HealthComponent.h"
#include "weapon/KineticWeapon.h"

namespace saga{
    class EnemyShip: public Ship{
    public:
        EnemyShip(World* world, const std::string& texturePath);

        void Tick(float deltaTime) override;
        void OnOverlap(Actor* other) override;

        void ApplyDamage(float amount);

        void SetTarget(Actor* target);

        CollisionShape GetCollisionShape() const override {return CollisionShape::Circle;}
        float GetCollisionRadius() const override {return 26.f;}

    private:
        unique<KineticWeapon> mWeapon;
        float mFireCooldown = 2.f;
        HealthComponent mHealth;
        Actor* mTarget;
        float mSpeed;
    };
}