#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"

namespace saga
{

    void PhysicsSystem::ProcessOverlaps(List<shared<Actor>> &actors)
    {
        //AABB Collision
        for(auto iterA = actors.begin(); iterA != actors.end(); ++iterA){
            auto iterB = iterA;
            ++iterB;
            for(;iterB != actors.end(); ++iterB){
                if(*iterA && *iterB && iterA->get() != iterB->get() &&
                 (*iterA)->GetActorBounds().findIntersection((*iterB)->GetActorBounds())){
                    (*iterA)->OnOverlap(iterB->get());
                    (*iterB)->OnOverlap(iterA->get());
                }
            }
        }
    }

} // namespace saga
