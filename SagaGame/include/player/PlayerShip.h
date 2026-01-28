#pragma once
#include "ship/Ship.h"

namespace saga{
    class PlayerShip: public Ship{
    public:
        PlayerShip(World* ownerWorld, const std::string& path = "PNG/Default/ship_F.png");
    };
}