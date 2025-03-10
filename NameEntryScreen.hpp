#ifndef NAMEENTRYSCREEN_HPP
#define NAMEENTRYSCREEN_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <string>

class Game;

class NameEntryScreen {
private:
    Game* game;
    sf::Font font;
    sf::Text promptText;
    sf::Text nameText;
    sf::String playerName;
public:
    NameEntryScreen(Game* game);
    void display(sf::RenderWindow &window);
    void handleInput(sf::RenderWindow &window);
    void resetName ();
};

#endif
