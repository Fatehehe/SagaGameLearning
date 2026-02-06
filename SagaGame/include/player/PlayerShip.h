#pragma once
#include "ship/Ship.h"
#include "components/HealthComponent.h"
#include "components/ShipStatsComponent.h"

namespace saga{
    class KineticWeapon;
    class PlayerShip: public Ship{
    public:
        PlayerShip(World* ownerWorld, const std::string& path = "PNG/Default/ship_F.png");
        virtual ~PlayerShip();

        const ShipStatsComponent& GetShipStats() const {return mShipStats;}
        
        void Tick(float deltaTime) override;

        float GetAimAngle() const {return mAimAngleDegrees;}
        void ApplyDamage(float amount);
        void Fire() override;

        CollisionShape GetCollisionShape() const override {return CollisionShape::Circle;}
        float GetCollisionRadius() const override {return 26.f;}
        bool IsDead() const {return mHealth.IsDead();}

    private:
        void ClampInputToWindow();
        void HandleInput();
        void TransformInput(float deltaTime);
        
        sf::Vector2f mMoveInput;
        float mAimAngleDegrees;

        HealthComponent mHealth;

        unique<KineticWeapon> mKineticWeapon;
    };
}