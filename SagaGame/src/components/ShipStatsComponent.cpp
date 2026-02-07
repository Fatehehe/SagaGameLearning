#include "components/ShipStatsComponent.h"

namespace saga
{
    
    ShipStatsComponent::ShipStatsComponent()
    :mProjectileDamage{10.f},
    mMoveSpeed{300.f},
    mMaxHealth{100.f}
    {
    }

    float ShipStatsComponent::GetProjectileDamage() const {return mProjectileDamage;}
    void ShipStatsComponent::SetProjectileDamage(float value){ mProjectileDamage = value; }

    float ShipStatsComponent::GetMoveSpeed() const {return mMoveSpeed;}
    void ShipStatsComponent::SetMoveSpeed(float value) {mMoveSpeed = value;}
    
    float ShipStatsComponent::GetMaxHealth() const {return mMaxHealth;}
    void ShipStatsComponent::SetMaxHealth(float value) {mMaxHealth = value;}
}
