#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "MenuScreen.hpp"
#include "Instructions.hpp"
#include "HighScore.hpp"
#include "BattleGround.hpp"
#include "GameOver.hpp"

class BattleGround;
class GameOver;

class Game {
public:
    enum GameState { MENU, INSTRUCTIONS, HIGHSCORE, BATTLE, GAME_OVER };
    static sf::Vector2u baseResolution;  // 🔹 Store base resolution
    static float scaleX, scaleY;         // 🔹 Store scaling factors
private:
    sf::RenderWindow window;
    GameState currentState;
    int score;
    MenuScreen menu;
    Instructions instructions;
    HighScore highScore;
    BattleGround* battleground;  // Change from direct object to pointer
    GameOver* gameOverScreen;
public:
    Game();
    void run();
    void changeState(GameState newState);
    sf::RenderWindow& getWindow();  // Function to get the window reference
    void addScore(int points);  // ✅ Function to increase score
    void saveScore();    
    int getScore ();
    void restartGame(bool isMenu);
};
#endif