#include "ship/Ship.h"

namespace saga
{
    Ship::Ship(World *ownerWorld, const std::string &texturePath)
    : Actor{ownerWorld, texturePath},
    mVelocity{}
    {

    }

    void Ship::Tick(float deltaTime){
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
    }

    void Ship::SetVelocity(sf::Vector2f newVelocity){
        mVelocity = newVelocity;
    }

    void Ship::Fire()
    {
    }
} // namespace saga

