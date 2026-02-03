#pragma once

#include "ship/Ship.h"
#include "components/HealthComponent.h"

namespace saga{
    class EnemyShip: public Ship{
    public:
        EnemyShip(World* world, const std::string& texturePath);

        void Tick(float deltaTime) override;
        void OnOverlap(Actor* other) override;

        void ApplyDamage(float amount);

        void SetTarget(Actor* target);

    private:
        HealthComponent mHealth;
        Actor* mTarget;
        float mSpeed;
    };
}