#pragma once

#include "framework/Actor.h"

namespace saga{

    enum class ProjectileType{
        Player,
        Enemy
    };

    class Projectile: public Actor{
    public:
        Projectile(World* world, Actor* owner, const std::string& texturePath, float speed = 200.f, float damage = 10.f);

        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);

        void BeginPlay() override;
        void Tick(float deltaTime) override;
        void OnOverlap(Actor* other)override;

        CollisionShape GetCollisionShape() const override {return CollisionShape::Circle;}
        float GetCollisionRadius() const override {return 8.f;}

        void SetProjectileType(ProjectileType projectileType) {mProjectileType = projectileType;}
        ProjectileType GetProjectileType() const {return mProjectileType;}

    private:
        void Move(float deltaTime);
        Actor* mOwner;
        float mSpeed;
        float mDamage;
        ProjectileType mProjectileType = ProjectileType::Player;
    };
}