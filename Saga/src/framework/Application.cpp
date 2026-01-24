#include <iostream>
#include "framework/Application.h"

namespace saga{
    Application::Application() 
    : mWindow{sf::VideoMode({800, 600}), "Saga Window"},
    mTargetFrameRate{60.f},
    mTickClock{}
    {

    }

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f/ mTargetFrameRate;

        while (mWindow.isOpen())
        {
            while (const std::optional event = mWindow.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    mWindow.close();
            }
            mWindow.clear(sf::Color::Black);
            mWindow.display();
        }

        accumulatedTime += mTickClock.restart().asSeconds();
        
        while(accumulatedTime >= targetDeltaTime){
            accumulatedTime -= targetDeltaTime;
            Tick(targetDeltaTime);
        }
    }
    
    void Application::Tick(float deltaTime)
    {
        std::cout << "update framerate: " << 1.f/deltaTime << std::endl;
    }
}
