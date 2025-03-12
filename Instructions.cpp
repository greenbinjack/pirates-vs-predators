#include "Constants.hpp"
#include "Game.hpp"
#include "Instructions.hpp"

#include <fstream>
#include <iostream>

Instructions::Instructions ()
{
    loadTexture (backgroundTexture, IMG_INSTRUCTIONS_SCREEN);
    background.setTexture (backgroundTexture);

    loadTexture (backButtonTexture, IMG_BACK_BUTTON);
    backButton.setTexture (backButtonTexture);
    backButton.setPosition (BACK_BUTTON_X, BACK_BUTTON_Y);
}

void
Instructions::display (sf::RenderWindow &window)
{
    window.draw (background);
    window.draw (backButton);
}

void
Instructions::handleInput (sf::RenderWindow &window, Game &game)
{
    if (sf::Mouse::isButtonPressed (sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition (window);
            if (backButton.getGlobalBounds ().contains (mousePos.x, mousePos.y))
                {
                    game.changeState (Game::MENU);
                }
        }
}