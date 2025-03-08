#pragma once
#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>

class Game;

class GameOver {
private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture menuButtonTexture;
    sf::Sprite menuButton;
    sf::Font font;
    sf::Text gameOverText;

public:
    GameOver();
    void display(sf::RenderWindow &window);
    void handleInput(sf::RenderWindow &window, Game &game);
};

#endif
