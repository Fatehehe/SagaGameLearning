#include "framework/Core.h"
#include "framework/Application.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

namespace saga{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style) 
    : mWindow{sf::VideoMode({windowWidth, windowHeight}), title, style},
    mTargetFrameRate{60.f},
    mTickClock{},
    currentWorld{nullptr},
    mCleanCycleClock{},
    mCleanCycleInterval{2.0f}
    {

    }

    Application::~Application(){}

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f/ mTargetFrameRate;

        //Main game loop
        while (mWindow.isOpen())
        {
            while (const std::optional event = mWindow.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    mWindow.close();
            }

            float frameRateDeltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += frameRateDeltaTime;
            
            while(accumulatedTime >= targetDeltaTime){
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }
            
        }
    }

    sf::Vector2u Application::GetWindowSize() const {
        return mWindow.getSize();
    }   

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);

        if(currentWorld){
            currentWorld->BeginPlayInternal();
            currentWorld->TickInternal(deltaTime);
        }

        if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval){
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
            if(currentWorld){
                currentWorld->CleanCycle();
            }
        }
    }

    void Application::Tick(float deltaTime)
    {
        
    }

    void Application::RenderInternal()
    {
        mWindow.clear(sf::Color::Black);
        Render(mWindow);
        mWindow.display();
    }

    void Application::Render(sf::RenderWindow& window)
    {
        if(currentWorld){
            currentWorld->Render(mWindow);
        }
    }
}