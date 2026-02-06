#include "weapon/Projectile.h"
#include "enemies/EnemyShip.h"
#include "player/PlayerShip.h"
#include "framework/World.h"

namespace saga{

    Projectile::Projectile(World *world, Actor *owner, const std::string &texturePath, float speed, float damage)
    : Actor{world, texturePath},
    mOwner{owner},
    mSpeed{speed},
    mDamage{damage}
    {

    }

    void Projectile::SetSpeed(float newSpeed)
    {
        mSpeed = newSpeed;
    }

    void Projectile::SetDamage(float newDamage)
    {
        mDamage = newDamage;
    }

    void Projectile::BeginPlay()
    {
        if(mSprite.has_value()){
            if(mProjectileType == ProjectileType::Player){
                mSprite->setColor(sf::Color::Cyan);
            }else{
                mSprite->setColor(sf::Color::Red);
            }
        }
    }

    void Projectile::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);
        if(IsActorOutOfBound()){
            Destroy();
        } 
    }

    void Projectile::OnOverlap(Actor *other)
    {
        if(other == mOwner) return;
        if(mProjectileType == ProjectileType::Player){
            if(auto enemy = dynamic_cast<EnemyShip*>(other)){
                enemy->ApplyDamage(mDamage);
                GetWorld()->QueueActorForImmediateRemoval(this);
            }
        }
        else if(mProjectileType == ProjectileType::Enemy){
            if(auto player = dynamic_cast<PlayerShip*>(other)){
                //TODO: Apply damage to player
                LOG("Damaging the player");
                GetWorld()->QueueActorForImmediateRemoval(this);
            }
        }
    }

    void Projectile::Move(float deltaTime)
    {
        float rotationDegrees = GetActorRotation();
        float rotationRadians = rotationDegrees * (3.14159265f/180.f);
        sf::Vector2f forward(std::sin(rotationRadians), -std::cos(rotationRadians));

        AddActorLocationOffset(forward * mSpeed * deltaTime);
    }
}
