#include "player/PlayerShip.h"

namespace saga{
    PlayerShip::PlayerShip(World *ownerWorld, const std::string &path)
    : Ship{ownerWorld, path},
    mMoveInput{},
    mSpeed{300.f}
    {

    }

    void PlayerShip::Tick(float deltaTime)
    {
        Ship::Tick(deltaTime);
        HandleInput();
        TransformInput(deltaTime);
    }

    void PlayerShip::HandleInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            mMoveInput.y = -1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            mMoveInput.y = 1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            mMoveInput.x = -1.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            mMoveInput.x = 1.f;
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

