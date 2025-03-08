/// Instructions.cpp - Implementation of Instructions Screen
#include "Instructions.hpp"
#include "Game.hpp"  // Add this line to access Game functions
#include <iostream>
#include <fstream>

Instructions::Instructions() {
    if (!backgroundTexture.loadFromFile("assets/instructions_screen.png")) {
        std::cerr << "Error loading instructions background!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    if (!backButtonTexture.loadFromFile("assets/back_button.png")) {
        std::cerr << "Error loading back button!" << std::endl;
    }
    backButton.setTexture(backButtonTexture);
    backButton.setPosition(50, 600);

    if (!font.loadFromFile("assets/custom_font.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    loadInstructions();
}

void Instructions::loadInstructions() {
    std::ifstream file("assets/ins.txt");
    if (!file) {
        std::cerr << "Error loading instructions text file!" << std::endl;
        return;
    }
    std::string line, content;
    while (getline(file, line)) {
        content += line + "\n";
    }
    file.close();

    instructionsText.setFont(font);
    instructionsText.setString(content);
    instructionsText.setCharacterSize(24);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(100, 150);
}

void Instructions::display(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(instructionsText);
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