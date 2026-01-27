#include "framework/Actor.h"
#include "framework/AssetManager.h"
// #include "Actor.h"

namespace saga{
    Actor::Actor(World *ownerWorld, const std::string& texturePath)
    : mOwnerWorld{ownerWorld}, 
    mHasBegunPlay{false}
    {
        SetTexturePath(texturePath);
    }

    Actor::~Actor()
    {
        LOG("Actor Destructor");
    }

    void Actor::BeginPlayInternal()
    {
        mHasBegunPlay = true;
        BeginPlay();
    }

    void Actor:: TickInternal(float deltaTime)
    {
        if(IsPendingDestroy() || !mSprite.has_value()) return;
        Tick(deltaTime);
    }

    void Actor::BeginPlay()
    {
        LOG("ACTOR BEGIN PLAY");
    }

    void Actor::Tick(float deltaTime)
    {
        // LOG("ACTOR BEGIN TICK");
    }

    void Actor::Render(sf::RenderWindow &renderWindow)
    {
        if(IsPendingDestroy()) return;
        renderWindow.draw(*mSprite);
    }

    void Actor::SetTexturePath(const std::string &texturePath)
    {
        if(texturePath.empty()){
            LOG("SetTexturePath empty");
            return;
        }

        mTexture = AssetManager::Get().LoadTexture(texturePath);
        if(!mTexture){
            LOG("Failed to load texture: %s", texturePath.c_str());
        }

        mSprite.emplace(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite->setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth,textureHeight}});
    }
}

