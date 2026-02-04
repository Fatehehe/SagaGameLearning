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
            for(; iterB !=  actors.end(); ++iterB){
                auto actorA = iterA->get();
                auto actorB = iterB->get();
                if(!actorA || !actorB || actorA == actorB) continue;

                if(CheckCollision(actorA, actorB)){
                    actorA->OnOverlap(actorB);
                    actorB->OnOverlap(actorA);
                }
            }
        }
    }

    bool PhysicsSystem::CheckCollision(Actor *actorA, Actor *actorB)
    {
        if(actorA->GetCollisionShape() == CollisionShape::Circle && actorB->GetCollisionShape() == CollisionShape::Circle ){
            sf::Vector2f delta = actorA->GetCollisionCenter() - actorB->GetCollisionCenter();
            float distanceSquared = delta.x * delta.x + delta.y * delta.y;
            float radiusSum = actorA->GetCollisionRadius() + actorB->GetCollisionRadius();

            return distanceSquared <= radiusSum * radiusSum;
        }
        return actorA->GetActorBounds().findIntersection(actorB->GetActorBounds()).has_value();
    }

} // namespace saga
