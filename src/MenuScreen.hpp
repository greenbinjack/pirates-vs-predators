#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <SFML/Graphics.hpp>

class Game;

class MenuScreen
{
  private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    sf::Texture startButtonTexture, instructionsButtonTexture, quitButtonTexture, highscoreButtonTexture;
    sf::Sprite startButton, instructionsButton, quitButton, highscoreButton;

  public:
    MenuScreen ();
    void display (sf::RenderWindow &window);
    void handleInput (sf::RenderWindow &window, Game &game);
};
#endif