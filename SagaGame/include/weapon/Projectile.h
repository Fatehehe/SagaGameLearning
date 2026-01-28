#pragma once

namespace saga
{
    class Actor;
    class Projectile {
    public:
        void Fire();
        virtual bool CanFire() const {return true;}
        virtual bool IsOnCooldown() const {return false;}
        Actor* GetOwner() const {return mOwner;}

    protected:
        Projectile(Actor* actor);

    private:
        virtual void FireImpl() = 0;
        Actor* mOwner;
    };
} // namespace saga
