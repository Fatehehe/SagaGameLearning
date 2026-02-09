#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace saga {
    class World;
    class Application{
    public:
        virtual ~Application();

        Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style );
        void Run();
        virtual void Render(sf::RenderWindow& window);

        template<typename WorldType>
        weak<WorldType> LoadWorld();

        sf::Vector2u GetWindowSize() const;
        sf::RenderWindow& GetRenderWindow() {return mWindow;}

    private:
        void TickInternal(float deltaTime);
        virtual void Tick(float deltaTime);
        void RenderInternal();

        sf::RenderWindow mWindow;
        float mTargetFrameRate; 
        sf::Clock mTickClock;
        sf::Clock mCleanCycleClock;
        float mCleanCycleInterval;

        shared<World> currentWorld;
    };

    template<typename WorldType>
    weak<WorldType> Application::LoadWorld(){
        shared<WorldType> newWorld{new WorldType{this}};
        currentWorld = newWorld;
        return newWorld;
    }
}