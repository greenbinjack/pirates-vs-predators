#ifndef GAME_HPP
#define GAME_HPP

#include "BattleGround.hpp"
#include "GameOver.hpp"
#include "HighScore.hpp"
#include "Instructions.hpp"
#include "MenuScreen.hpp"
#include "NameEntryScreen.hpp"
#include <SFML/Graphics.hpp>

class BattleGround;

class Game
{
  public:
    enum GameState
    {
        MENU,
        ENTER_NAME,
        INSTRUCTIONS,
        HIGHSCORE,
        BATTLE,
        GAME_OVER
    };
    static sf::Vector2u baseResolution;

  private:
    sf::RenderWindow window;
    GameState currentState;
    MenuScreen menu;
    Instructions instructions;
    HighScore highScore;
    BattleGround *battleground;
    GameOver gameOverScreen;
    NameEntryScreen nameEntryScreen;
    int score;
    std::string playerName;

  public:
    Game ();
    void run ();
    void changeState (GameState newState);
    sf::RenderWindow &getWindow ();
    void addScore (int points);
    void saveScore ();
    int getScore ();
    void resetScore ();
    void restartGame (bool isMenu);
    void setPlayerName (const std::string &name);
};
#endif