#pragma once
#include "framework/Actor.h"
#include "components/ShipStatsComponent.h"

namespace saga{
    class Ship: public Actor{
    public:
        Ship(World* ownerWorld, const std::string& texturePath = "");
        const ShipStatsComponent& GetShipStatsComponent() const {return mShipStats;}
        // ShipStatsComponent& GetMutableShipStats() {return mShipStats;}

        virtual void Tick(float deltaTime) override;

        void SetVelocity(sf::Vector2f newVelocity);
        sf::Vector2f GetVelocity() const {return mVelocity;}

        virtual float GetProjectileDamage() const {return mShipStats.GetProjectileDamage();}
        
        virtual void Fire();
    protected:
        ShipStatsComponent mShipStats;

    private:
        sf::Vector2f mVelocity;
    };
}