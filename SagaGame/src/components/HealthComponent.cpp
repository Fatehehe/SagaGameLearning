#include "components/HealthComponent.h"

namespace saga
{
    
    HealthComponent::HealthComponent(float maxHealth)
    : mMaxHealth{maxHealth},
    mHealth{maxHealth}
    {

    }

    void HealthComponent::ApplyDamage(float damage)
    {
        mHealth -= damage;
        if(mHealth <= 0.f){
            mHealth = 0.f;
        }
    }

    bool HealthComponent::IsDead() const
    {
        return mHealth <= 0;
    }
} // namespace saga