#include "weapon/KineticWeapon.h"
#include "player/PlayerShip.h"
#include "SFML/Graphics.hpp"

namespace saga{
    PlayerShip::PlayerShip(World *ownerWorld, const std::string &path)
    : Ship{ownerWorld, path},
    mMoveInput{},
    mSpeed{300.f},
    mKineticWeapon{new KineticWeapon{this, 1.f}}
    {

    }

    PlayerShip::~PlayerShip() = default;

    void PlayerShip::Tick(float deltaTime)
    {
        Ship::Tick(deltaTime);
        HandleInput();
        TransformInput(deltaTime);
    }

    void PlayerShip::Fire()
    {
        if(mKineticWeapon){
            mKineticWeapon->Fire();
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
            Fire();
        }
    }

    void PlayerShip::TransformInput(float deltaTime)
    {
        if(mMoveInput != sf::Vector2f{0.f,0.f}){
            mMoveInput = mMoveInput.normalized();
        }
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput = sf::Vector2f{0.f,0.f};
    }
}

