#include <iostream>
#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "player/PlayerShip.h"
#include "enemies/EnemyShip.h"
#include "framework/AssetManager.h"
#include "config.h"

namespace saga{
    Application *GetApplication()
    {
        return new GameApplication();
    }

    GameApplication::GameApplication()
    : Application{800,600, "Saga Window", sf::Style::Titlebar | sf::Style::Close},
    mSpawnInterval{1.5f},
    mKillCountText{mFont},
    mEnemyKillCount{0},
    mTitleText{mFont, "", 48},
    mHealthText{mFont, "", 18},
    mStartPromptText{mFont, "", 24},
    mGameOverText{mFont, "", 48},
    mFinalScoreText{mFont, "", 24}
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());

        if(!mFont.openFromFile(GetResourceDirectory() + "Fonts/Kenney Future.ttf")){
            std::cerr << "Failed to load font" << std::endl;
        }
        //Title text
        mTitleText.setFont(mFont);
        mTitleText.setString("BULLET SAGA");
        mTitleText.setCharacterSize(48);
        mTitleText.setFillColor(sf::Color::White);
        mTitleText.setPosition(sf::Vector2f{200.f, 150.f});

        //Health text
        mHealthText.setFont(mFont);
        mHealthText.setString("100/100");
        mHealthText.setCharacterSize(18);
        mHealthText.setFillColor(sf::Color::Black);
        mHealthText.setPosition(sf::Vector2f{600.f, 10.f});

        //Health Bar
        mHealthBarBack.setSize(sf::Vector2f{200.f, 20.f});
        mHealthBarBack.setFillColor(sf::Color::White);
        mHealthBarBack.setPosition(sf::Vector2f{580.f, 10.f});

        //HealthBar fill
        mHealthBarFill.setSize(sf::Vector2f{200.f, 10.f});
        mHealthBarFill.setFillColor(sf::Color(242, 160, 23));
        mHealthBarFill.setPosition(sf::Vector2f{580.f, 10.f});

        //Start prompt
        mStartPromptText.setFont(mFont);
        mStartPromptText.setString("Press Enter to Start");
        mStartPromptText.setCharacterSize(24);
        mStartPromptText.setFillColor(sf::Color::White);
        mStartPromptText.setPosition(sf::Vector2f{200.f, 250.f});
        
        //gameover text
        mGameOverText.setFont(mFont);
        mGameOverText.setString("GAME OVER");
        mGameOverText.setCharacterSize(48);
        mGameOverText.setFillColor(sf::Color::Red);
        mGameOverText.setPosition(sf::Vector2f{200.f, 150.f});

        //final score text
        mFinalScoreText.setFont(mFont);
        // mFinalScoreText.setString("Press Enter to Start");
        mFinalScoreText.setCharacterSize(24);
        mFinalScoreText.setFillColor(sf::Color::White);
        mFinalScoreText.setPosition(sf::Vector2f{200.f, 250.f});

        //Kill UI
        mKillCountText.setFont(mFont);
        mKillCountText.setCharacterSize(18);
        mKillCountText.setFillColor(sf::Color::White);
        mKillCountText.setPosition(sf::Vector2f{10.f,10.f});
        mKillCountText.setString("Kills: 0");

        mWorld = LoadWorld<World>(); 
        playerShip = mWorld.lock()->SpawnActor<PlayerShip>();
        playerShip.lock()->SetActorLocation(sf::Vector2f{400.f, 300.f});
        playerShip.lock()->SetActorRotation(0.0f);
    }

    void GameApplication::Tick(float deltaTime)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
            if(mGameState == GameState::MainMenu){
                StartGame();
            }else if(mGameState == GameState::GameOver){
                RestartGame();
            }

            if(mGameState == GameState::Running){
                return;
            }
        }
        if(mEnemySpawnClock.getElapsedTime().asSeconds() > mSpawnInterval){
            mEnemySpawnClock.restart();
            SpawnEnemy();
        }

        if(!playerShip.expired()){
            float health = playerShip.lock()->GetHealth();
            float maxHealth = playerShip.lock()->GetMaxHealth();
            mHealthText.setString(std::to_string(static_cast<int>(health)) + "/" + std::to_string(static_cast<int>(maxHealth)));

            float healthPercent = playerShip.lock()->GetHealthPercentage();
            float barWidth = 200.f * std::clamp(healthPercent, 0.f, 1.f);
            mHealthBarFill.setSize(sf::Vector2f{barWidth, 20.f});

        }
    }

    void GameApplication::Render(sf::RenderWindow &window){
        if(mGameState == GameState::MainMenu){
            window.draw(mTitleText);
            window.draw(mStartPromptText);
            return;
        }
        if(mGameState == GameState::GameOver){
            window.draw(mGameOverText);
            window.draw(mFinalScoreText);
            return;
        }

        Application::Render(window);
        window.draw(mKillCountText);
        window.draw(mHealthBarBack);
        window.draw(mHealthBarFill);
        window.draw(mHealthText);
    }

    void GameApplication::AddEnemyKill()
    {
        ++mEnemyKillCount;
        // LOG("Enemy kill count: %d", mEnemyKillCount);
        mKillCountText.setString("Kills: " + std::to_string(mEnemyKillCount));

        if(!playerShip.expired()){
            auto player = playerShip.lock();
            if(mEnemyKillCount == 10){
                player->UpgradeToSpreadShot();
            }
        }
    }

    void GameApplication::OnPlayerDeath()
    {
        mGameState = GameState::GameOver;
        mFinalScoreText.setString("Kills: " + std::to_string(mEnemyKillCount) + "\nPress Enter to Restart");
    }

    void GameApplication::SpawnEnemy()
    {
        auto world = mWorld.lock();
        auto player = playerShip.lock();
        if(!world || !player) return;

        sf::Vector2u windowSize = GetWindowSize();
        int side = rand() % 4;
        sf::Vector2f spawnPos;

        switch(side){
            //Top
            case 0: spawnPos = {static_cast<float>(rand() % windowSize.x), -50.f}; break;
            //right
            case 1: spawnPos = {static_cast<float>(windowSize.x + 50.f), static_cast<float>(rand() % windowSize.y)}; break;
            //bottom
            case 2: spawnPos = {static_cast<float>(rand() % windowSize.x), static_cast<float>(windowSize.y + 50.f)}; break;
            //Left
            case 3: spawnPos = {-50.f, static_cast<float>(rand() % windowSize.y)}; break;
        }

        weak<EnemyShip> enemy = world->SpawnActor<EnemyShip>("PNG/Default/enemy_A.png");
        enemy.lock()->SetActorLocation(spawnPos);
        enemy.lock()->SetActorRotation(180.f);
        enemy.lock()->SetTarget(player.get());
    }

    void GameApplication::StartGame()
    {
        mGameState = GameState::Running;
        mEnemyKillCount = 0;
        mWorld = LoadWorld<World>();
        playerShip = mWorld.lock()->SpawnActor<PlayerShip>();
        playerShip.lock()->SetActorLocation(sf::Vector2f{400.f, 300.f});
        playerShip.lock()->SetActorRotation(0.f);

        mKillCountText.setString("Kills: 0");
    }
    
    void GameApplication::RestartGame()
    {
        mGameState = GameState::MainMenu;
    }
}

