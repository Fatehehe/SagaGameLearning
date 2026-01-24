#pragma once
#include <SFML/Graphics.hpp>

namespace saga {
    class Application{
    public:
        Application();
        void Run();
    private:
        void Tick(float deltaTime);

        sf::RenderWindow mWindow;
        float mTargetFrameRate; 
        sf::Clock mTickClock;

    };
}