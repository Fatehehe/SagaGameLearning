#pragma once
#include "ship/Ship.h"

namespace saga{
    class KineticWeapon;
    class PlayerShip: public Ship{
    public:
        PlayerShip(World* ownerWorld, const std::string& path = "PNG/Default/ship_F.png");
        virtual ~PlayerShip();
        
        virtual void Tick(float deltaTime) override;
        
        void SetSpeed(float newSpeed) {mSpeed = newSpeed; }
        float GetSpeed() const {return mSpeed;}

        float GetAimAngle() const {return mAimAngleDegrees;}
        virtual void Fire() override;

        CollisionShape GetCollisionShape() const override {return CollisionShape::Circle;}
        float GetCollisionRadius() const override {return 26.f;}

    private:
        void ClampInputToWindow();
        void HandleInput();
        void TransformInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;
        float mAimAngleDegrees;

        unique<KineticWeapon> mKineticWeapon;
    };
}