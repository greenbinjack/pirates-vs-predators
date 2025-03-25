#ifndef NAMEENTRYSCREEN_HPP
#define NAMEENTRYSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Game;

class NameEntryScreen
{
  private:
    sf::Font font;
    sf::Text promptText;
    sf::Text nameText;
    sf::String playerName;

  public:
    NameEntryScreen ();
    void display (sf::RenderWindow &window);
    void handleInput (sf::RenderWindow &window, Game &game);
    void resetName ();
};

#endif
