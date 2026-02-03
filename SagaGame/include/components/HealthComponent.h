#pragma once

namespace saga
{
    class HealthComponent{
    public:
        HealthComponent(float maxHealth);

        void ApplyDamage(float damage);
        bool IsDead() const;
        float GetHealth() const {return mHealth;}
    private:
        float mHealth;
        float mMaxHealth;
    };
} // namespace saga
