/// MenuScreen.cpp - Implementation of MenuScreen Class
#include "MenuScreen.hpp"
#include "Game.hpp"  // Add this line to access Game functions
#include <iostream>

#include "MenuScreen.hpp"
#include "Game.hpp"
#include <iostream>

MenuScreen::MenuScreen() {
    if (!backgroundTexture.loadFromFile("assets/menuscreen.png")) {
        std::cerr << "[ERROR] Failed to load menu background!" << std::endl;
    } else {
        background.setTexture(backgroundTexture);
    }

    if (!startButtonTexture.loadFromFile("assets/start_button.png") ||
        !instructionsButtonTexture.loadFromFile("assets/instructions_button.png") ||
        !quitButtonTexture.loadFromFile("assets/quit_button.png") ||
        !highscoreButtonTexture.loadFromFile("assets/highscore_button.png")) {
        std::cerr << "Error loading menu buttons!" << std::endl;
    }

    // Set Button Textures
    startButton.setTexture(startButtonTexture);
    instructionsButton.setTexture(instructionsButtonTexture);
    quitButton.setTexture(quitButtonTexture);
    highscoreButton.setTexture(highscoreButtonTexture);

    // 🔹 Define Grid Layout (Centered)
    float centerX = 1200;  // Screen center
    float centerY = 800;  // Screen center

    float buttonWidth = 300.0f;
    float buttonHeight = 150.0f;
    float spacing = 50.0f;  // Space between buttons

    float topLeftX = centerX - (buttonWidth + spacing / 2);
    float topLeftY = centerY - (buttonHeight + spacing / 2);

    // 🔹 Arrange Buttons in 2x2 Grid
    startButton.setPosition(topLeftX, topLeftY);  // Top-left
    instructionsButton.setPosition(topLeftX + buttonWidth + spacing, topLeftY);  // Top-right
    highscoreButton.setPosition(topLeftX, topLeftY + buttonHeight + spacing);  // Bottom-left
    quitButton.setPosition(topLeftX + buttonWidth + spacing, topLeftY + buttonHeight + spacing);  // Bottom-right

    // 🔹 Scale Buttons Properly (Ensure 300x150)
    float actualWidth = startButton.getGlobalBounds().width;
    float actualHeight = startButton.getGlobalBounds().height;

    startButton.setScale(buttonWidth / actualWidth, buttonHeight / actualHeight);
    instructionsButton.setScale(buttonWidth / actualWidth, buttonHeight / actualHeight);
    highscoreButton.setScale(buttonWidth / actualWidth, buttonHeight / actualHeight);
    quitButton.setScale(buttonWidth / actualWidth, buttonHeight / actualHeight);
}

void MenuScreen::display(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(startButton);
    window.draw(instructionsButton);
    window.draw(highscoreButton);
    window.draw(quitButton);
}

void MenuScreen::handleInput(sf::RenderWindow &window, Game &game) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
           

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            std::cout << "[DEBUG] Mouse Clicked at: X=" << worldPos.x << ", Y=" << worldPos.y << std::endl;

            if (startButton.getGlobalBounds().contains(worldPos)) {
                std::cout << "[DEBUG] Start Button Clicked!" << std::endl;
                game.changeState(Game::ENTER_NAME);
            } else if (instructionsButton.getGlobalBounds().contains(worldPos)) {
                std::cout << "[DEBUG] Instructions Button Clicked!" << std::endl;
                game.changeState(Game::INSTRUCTIONS);
            } else if (highscoreButton.getGlobalBounds().contains(worldPos)) {
                std::cout << "[DEBUG] Highscore Button Clicked!" << std::endl;
                game.changeState(Game::HIGHSCORE);
            } else if (quitButton.getGlobalBounds().contains(worldPos)) {
                std::cout << "[DEBUG] Quit Button Clicked!" << std::endl;
                window.close();
            }
        }
    }
}
