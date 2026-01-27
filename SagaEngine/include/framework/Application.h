#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace saga {
    class World;
    class Application{
    public:
        Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, std::uint32_t style );
        void Run();

        template<typename WorldType>
        weak<WorldType> LoadWorld();

    private:
        void TickInternal(float deltaTime);
        virtual void Tick(float deltaTime);
        void RenderInternal();
        virtual void Render();

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