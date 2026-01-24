#pragma once
#include <SFML/Graphics.hpp>

namespace saga {
    class Application{
    public:
        Application();
        void Run();
    private:
        sf::RenderWindow mWindow;
    };
}