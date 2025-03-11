#include "Instructions.hpp"
#include "Game.hpp"  
#include "Constants.hpp"

#include <iostream>
#include <fstream>

Instructions::Instructions() {
    loadTexture (backgroundTexture, "assets/instructions_screen.png");
    background.setTexture(backgroundTexture);

    loadTexture (backButtonTexture, "assets/back_button.png");
    backButton.setTexture(backButtonTexture);
    backButton.setPosition(BACK_BUTTON_X, BACK_BUTTON_Y);
}

void Instructions::display(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(backButton);
}

void Instructions::handleInput(sf::RenderWindow &window, Game &game) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            game.changeState(Game::MENU);
        }
    }
}