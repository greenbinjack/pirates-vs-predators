#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "Instructions.hpp"
#include "HighScore.hpp"
#include "BattleGround.hpp"
#include "GameOver.hpp"
#include "NameEntryScreen.hpp"

class BattleGround;
class GameOver;
class NameEntryScreen;

class Game {
public:
    enum GameState { MENU, ENTER_NAME, INSTRUCTIONS, HIGHSCORE, BATTLE, GAME_OVER };
    static sf::Vector2u baseResolution;  // 🔹 Store base resolution
    static float scaleX, scaleY;         // 🔹 Store scaling factors
private:
    sf::RenderWindow window;
    GameState currentState;
    int score;
    std::string playerName;  // ✅ Store player's name
    MenuScreen menu;
    Instructions instructions;
    HighScore highScore;
    BattleGround* battleground;  // Change from direct object to pointer
    GameOver* gameOverScreen;
    NameEntryScreen* nameEntryScreen;
public:
    Game();
    void run();
    void changeState(GameState newState);
    sf::RenderWindow& getWindow();  // Function to get the window reference
    void addScore(int points);  // ✅ Function to increase score
    void saveScore();    
    int getScore ();
    void restartGame(bool isMenu);
    void setPlayerName(const std::string &name);  // ✅ Function to set player's name
    std::string getPlayerName() const;  // ✅ Function to get player's name
};
#endif