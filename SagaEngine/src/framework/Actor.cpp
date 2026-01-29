#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/World.h"

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
            // LOG("SetTexturePath empty");
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
        CenterPivot();
    }
    
    void Actor::SetActorLocation(const sf::Vector2f &newLocation)
    {   
        mSprite->setPosition(newLocation);
    }

    void Actor::SetActorRotation(float newRotation)
    {
        mSprite->setRotation(sf::degrees(newRotation));
    }
    
    sf::Vector2f Actor::GetActorLocation() const
    {
        return mSprite->getPosition();
    }

    float Actor::GetActorRotation() const
    {
        return mSprite->getRotation().asDegrees();
    }

    sf::FloatRect Actor::GetActorBounds() const
    {
        return mSprite->getGlobalBounds();
    }
    
    void Actor::AddActorLocationOffset(const sf::Vector2f &offsetAmt)
    {
        SetActorLocation(GetActorLocation() + offsetAmt);
    }

    void Actor::AddActorLocationOffset(float offsetAmt)
    {
        SetActorRotation(GetActorRotation() + offsetAmt);
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwnerWorld->GetWindowSize();
    }

    bool Actor::IsActorOutOfBound() const
    {
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float actorWidth = GetActorBounds().size.x;
        float actorHeight = GetActorBounds().size.y;
        
        sf::Vector2f actorPos = GetActorLocation();

        if(actorPos.x < -actorWidth){
            return true;
        }
        if(actorPos.x > windowWidth + actorWidth){
            return true;
        }
        if(actorPos.y < -actorHeight){
            return true;
        }
        if(actorPos.y > windowHeight + actorHeight){
            return true;
        } 

        return false;
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bounds = mSprite->getGlobalBounds();
        mSprite->setOrigin(bounds.getCenter());
    }
}
