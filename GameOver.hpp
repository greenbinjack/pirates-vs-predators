#pragma once
#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"

class GameOver {
private:
    Game* game;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture menuButtonTexture;
    sf::Sprite menuButton;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text finalScoreText; 
    sf::Text playerNameText;
public:
    GameOver(Game* game);
    void display(sf::RenderWindow &window);
    void handleInput(sf::RenderWindow &window);
    void updateFinalScore(int score, const std::string &name);
};

#endif
