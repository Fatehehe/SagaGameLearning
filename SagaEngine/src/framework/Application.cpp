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
            RenderInternal();
        }

        accumulatedTime += mTickClock.restart().asSeconds();
        
        while(accumulatedTime >= targetDeltaTime){
            accumulatedTime -= targetDeltaTime;
            TickInternal(targetDeltaTime);
        }
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
    }

    void Application::Tick(float deltaTime)
    {
        std::cout << deltaTime << std::endl;
    }

    void Application::RenderInternal()
    {
        mWindow.clear(sf::Color::Black);
        Render();
        mWindow.display();
    }

    void Application::Render()
    {
        
        sf::RectangleShape rect(sf::Vector2f({100.f, 100.f}));
        rect.setFillColor(sf::Color::Red);
        rect.setOrigin(sf::Vector2f(50,50));
        rect.setPosition(sf::Vector2f(mWindow.getSize().x/2, mWindow.getSize().y/2));
        mWindow.draw(rect);
    }
}