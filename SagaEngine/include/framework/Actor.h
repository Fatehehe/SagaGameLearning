#pragma once

#include "framework/Core.h"
#include "framework/Object.h"
#include "SFML/Graphics.hpp"

namespace saga{
    class World;
    class Actor: public Object{
    public:
        Actor(World* ownerWorld, const std::string& texturePath = "");
        virtual ~Actor();

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        void Render(sf::RenderWindow& renderWindow);

        void SetTexturePath(const std::string& texturePath);
    
    private:
        World* mOwnerWorld;
        bool mHasBegunPlay;

        sf::Sprite mSprite;
        sf::Texture mTexture;
    };
}