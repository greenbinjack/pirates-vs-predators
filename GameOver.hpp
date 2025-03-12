#pragma once
#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>

class Game;

class GameOver
{
  private:
    sf::Texture menuButtonTexture;
    sf::Sprite menuButton;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text finalScoreText;
    sf::Text playerNameText;

  public:
    GameOver ();
    void display (sf::RenderWindow &window);
    void handleInput (sf::RenderWindow &window, Game &game);
    void updateFinalScore (int score, const std::string &name);
};

#endif
