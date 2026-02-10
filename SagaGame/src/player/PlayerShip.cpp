#include "weapon/KineticWeapon.h"
#include "weapon/SpreadShotWeapon.h"
#include "player/PlayerShip.h"
#include "SFML/Graphics.hpp"
#include "framework/World.h"
#include "gameFramework/GameApplication.h"

namespace saga{
    PlayerShip::PlayerShip(World *ownerWorld, const std::string &path)
    : Ship{ownerWorld, path},
    mMoveInput{},
    mAimAngleDegrees{0.f},
    mHealth{100.f}
    {
        mShipStats.SetProjectileDamage(50.f);
        mShipStats.SetMoveSpeed(400.f);
        mShipStats.SetMaxHealth(100.f);
        
        mHealth = HealthComponent{mShipStats.GetMaxHealth()};
        mKineticWeapon = std::make_unique<KineticWeapon>(this, .3f);
    }

    PlayerShip::~PlayerShip() = default;

    void PlayerShip::Tick(float deltaTime)
    {
        Ship::Tick(deltaTime);
        HandleInput();
        TransformInput(deltaTime);
    }

    void PlayerShip::UpgradeToSpreadShot()
    {
        if(!mHasWeaponUpgraded){
            mHasWeaponUpgraded = true;
            LOG("Upgraded weapon to SpreadShot!");
            mKineticWeapon = std::make_unique<SpreadShotWeapon>(this, 0.5f, 3, 45.f);
        }
    }

    void PlayerShip::Fire()
    {
        sf::RenderWindow& window = GetWorld()->GetRenderWindow();
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

        sf::Vector2f toMouse = mouseWorldPos - GetActorLocation();

        if(toMouse != sf::Vector2f{0.f,0.f}){
            float angleRadians = std::atan2(toMouse.y, toMouse.x);
            float angleDegrees = sf::radians(angleRadians).asDegrees();
            mAimAngleDegrees = angleDegrees + 90.f;
        }

        if(mKineticWeapon){
            mKineticWeapon->Fire();
        }
    }

    void PlayerShip::ApplyDamage(float amount)
    {
        mHealth.ApplyDamage(amount);
        LOG("Damage dealt: %f", mHealth.GetHealth());
        if(mHealth.IsDead()){
            GetWorld()->QueueActorForImmediateRemoval(this);
            //TODO: Trigger Game Over
            if(auto* app = dynamic_cast<GameApplication*>(GetWorld()->GetApplication())){
                app->OnPlayerDeath();
            }
        }
    }

    void PlayerShip::ClampInputToWindow()
    {
        sf::Vector2f actorLocation = GetActorLocation();
        if(actorLocation.x < 0 && mMoveInput.x == -1.f){
            mMoveInput.x = 0.f;
        }

        if(actorLocation.x > GetWindowSize().x && mMoveInput.x == 1.f){
            mMoveInput.x = 0.f;
        }

        if(actorLocation.y < 0 && mMoveInput.y == -1.f){
            mMoveInput.y = 0.f;
        }

        if(actorLocation.y > GetWindowSize().y && mMoveInput.y == 1.f){
            mMoveInput.y = 0.f;
        }
    }

    void PlayerShip::HandleInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            mMoveInput.y = -1.f;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            mMoveInput.y = 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            mMoveInput.x = -1.f;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            mMoveInput.x = 1.f;
        }
        ClampInputToWindow();

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            Fire();
        }
    }

    void PlayerShip::TransformInput(float deltaTime)
    {
        if(mMoveInput != sf::Vector2f{0.f,0.f}){
            mMoveInput = mMoveInput.normalized();

            float angleRadians = std::atan2(mMoveInput.y, mMoveInput.x);
            float angleDegrees = sf::radians(angleRadians).asDegrees();
            SetActorRotation(angleDegrees + 90.f);

            SetVelocity(mMoveInput * mShipStats.GetMoveSpeed());
        }else{
            SetVelocity(sf::Vector2f{0.f, 0.f});
        }
        mMoveInput = sf::Vector2f{0.f,0.f};
    }
}

