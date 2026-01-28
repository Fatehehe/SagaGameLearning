#pragma once
#include "framework/Actor.h"

namespace saga{
    class Ship: public Actor{
    public:
        Ship(World* ownerWorld, const std::string& texturePath = "");
        virtual void Tick(float deltaTime) override;

        void SetVelocity(sf::Vector2f newVelocity);
        sf::Vector2f GetVelocity() const {return mVelocity;}
        
    private:
        sf::Vector2f mVelocity;
    };
}