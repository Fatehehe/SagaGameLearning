#pragma once

#include "framework/Core.h"

namespace saga{
    class Actor;
    class PhysicsSystem{
    public:
        static void ProcessOverlaps(List<shared<Actor>>& actors);
        static bool CheckCollision(Actor* actorA, Actor* actorB);
    };
}