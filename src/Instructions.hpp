#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Game;

class Instructions
{
  private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture backButtonTexture;
    sf::Sprite backButton;

  public:
    Instructions ();
    void display (sf::RenderWindow &window);
    void handleInput (sf::RenderWindow &window, Game &game);
};

#endif