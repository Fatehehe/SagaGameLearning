#pragma once

namespace saga
{
    class ShipStatsComponent{
    public:
        ShipStatsComponent();

        float GetProjectileDamage() const;
        void SetProjectileDamage(float value);

        float GetMoveSpeed() const;
        void SetMoveSpeed(float value);

        float GetFireCooldown() const;
        void SetFireCooldown(float value);

        float GetMaxHealth() const;
        void SetMaxHealth(float value);

    private:
        float mProjectileDamage;
        float mMoveSpeed;
        float mFireCooldown;
        float mMaxHealth;
    };
} // namespace saga
