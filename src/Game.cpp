#include "Constants.hpp"
#include "Game.hpp"
#include <iostream>

sf::Vector2u Game::baseResolution = sf::Vector2u (WINDOW_WIDTH, WINDOW_HEIGHT);

Game::Game () : window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), "Pirates vs Predators"), currentState (MENU), score (0) { battleground = new BattleGround (this); }

sf::RenderWindow &
Game::getWindow ()
{
    return window;
}

void
Game::run ()
{
    sf::Clock clock;

    while (window.isOpen ())
        {
            float deltaTime = clock.restart ().asSeconds ();
            window.clear ();

            switch (currentState)
                {
                case MENU:
                    menu.handleInput (window, *this);
                    menu.display (window);
                    break;
                case ENTER_NAME:
                    nameEntryScreen.handleInput (window, *this);
                    nameEntryScreen.display (window);
                    break;
                case INSTRUCTIONS:
                    instructions.display (window);
                    instructions.handleInput (window, *this);
                    break;
                case HIGHSCORE:
                    highScore.display (window);
                    highScore.handleInput (window, *this);
                    break;
                case BATTLE:
                    battleground->handleInput (window);
                    battleground->update (deltaTime);
                    battleground->render (window);
                    break;
                case GAME_OVER:
                    gameOverScreen.updateFinalScore (score, playerName);
                    gameOverScreen.display (window);
                    gameOverScreen.handleInput (window, *this);
                    break;
                }

            window.display ();
        }
}

void
Game::changeState (GameState newState)
{
    currentState = newState;
}

void
Game::restartGame (bool isMenu)
{
    std::cout << "[DEBUG] Restarting the Game..." << std::endl;

    delete battleground;
    battleground = new BattleGround (this);

    if (isMenu)
        {
            changeState (MENU);
            score = 0;
            playerName.clear ();
            nameEntryScreen.resetName ();
        }
    else
        {
            score = 0;
            changeState (BATTLE);
        }
}

void
Game::addScore (int points)
{
    score += points;
    std::cout << "[DEBUG] Score: " << score << std::endl;
}

void
Game::saveScore ()
{
    highScore.addNewScore (score, playerName);
    score = 0;
    playerName.clear ();
}

int
Game::getScore ()
{
    return score;
}

void
Game::setPlayerName (const std::string &name)
{
    playerName = name;
}

void
Game::resetScore () 
{
    score = 0;
}