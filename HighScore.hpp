/// HighScore.hpp - Header file for HighScore management
#pragma once
#ifndef HIGHSCORE_HPP
#define HIGHSCORE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Game;

class HighScore {
private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture backButtonTexture;
    sf::Sprite backButton;
    sf::Font font;
    sf::Text highScoreText;
    std::vector<int> scores;
    void loadScores();
    void saveScores();
    void updateHighScoreText();
public:
    HighScore();
    void display(sf::RenderWindow &window);
    void handleInput(sf::RenderWindow &window, Game &game);
    void addNewScore(int score);
};

#endif // HIGHSCORE_HPP