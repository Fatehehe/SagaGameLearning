#pragma once
#include "ship/Ship.h"

namespace saga{
    class PlayerShip: public Ship{
    public:
        PlayerShip(World* ownerWorld, const std::string& path = "PNG/Default/ship_F.png");
        
        virtual void Tick(float deltaTime) override;
        
        void SetSpeed(float newSpeed) {mSpeed = newSpeed; }
        float GetSpeed() const {return mSpeed;}

    private:
        void HandleInput();
        void TransformInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;
    };
}