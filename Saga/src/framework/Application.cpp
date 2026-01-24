#include "framework/Application.h"

namespace saga{
    Application::Application() 
    : mWindow{sf::VideoMode({800, 600}), "Saga Window"}
    {

    }

    void Application::Run()
    {
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
    }
}

