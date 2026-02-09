#pragma once

#include "framework/Application.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace saga{
    enum class GameState {
        MainMenu,
        Running,
        GameOver
    };

    class PlayerShip;
    class GameApplication: public Application{
    public:
        GameApplication();
        void Tick(float deltaTime) override;
        void Render(sf::RenderWindow &window) override;

        void AddEnemyKill();
        int GetEnemyKillCount() const {return mEnemyKillCount;}

        void OnPlayerDeath();

    private:
        GameState mGameState = GameState::MainMenu;

        sf::Text mTitleText;
        sf::Text mStartPromptText;
        sf::Text mGameOverText;
        sf::Text mFinalScoreText;

        weak<PlayerShip> playerShip;
        weak<World> mWorld;

        sf::Clock mEnemySpawnClock;
        float mSpawnInterval;
        void SpawnEnemy();

        int mEnemyKillCount = 0;
        sf::Font mFont;
        sf::Text mKillCountText;
        sf::RectangleShape mHealthBarBack;
        sf::RectangleShape mHealthBarFill;

        sf::Text mHealthText;

        void StartGame();
        void RestartGame();
    };
}