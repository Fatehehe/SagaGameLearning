#pragma once
#include "weapon/Weapon.h"
#include "weapon/KineticWeapon.h"

namespace saga
{
    class SpreadShotWeapon : public KineticWeapon {
    public:
        SpreadShotWeapon(Actor* owner, float cooldownTime, int numProjectiles = 3, float spreadAngle = 20.f);

    protected:
        void FireImpl() override;
    
    private:
        int mNumProjectiles;
        float mSpreadAngle;
    };
} // namespace saga
