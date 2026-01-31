#pragma once

#include "framework/Core.h"

namespace saga{
    class Actor;
    class PhysicsSystem{
    public:
        void ProcessOverlaps(List<shared<Actor>>& actors);
    };
}