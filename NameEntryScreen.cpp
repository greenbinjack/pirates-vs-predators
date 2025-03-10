#include "NameEntryScreen.hpp"
#include <iostream>

NameEntryScreen::NameEntryScreen(Game* game) : game(game) {
    if (!font.loadFromFile("assets/custom_font.ttf")) {
        std::cerr << "[ERROR] Failed to load font!" << std::endl;
    }

    promptText.setFont(font);
    promptText.setCharacterSize(72);
    promptText.setFillColor(sf::Color::White);
    promptText.setString("Enter Your Name:");
    promptText.setPosition(700, 400);

    nameText.setFont(font);
    nameText.setCharacterSize(72);
    nameText.setFillColor(sf::Color::Yellow);
    nameText.setPosition(700, 500);
}

void NameEntryScreen::display(sf::RenderWindow &window) {
    window.clear();
    window.draw(promptText);
    window.draw(nameText);
    window.display();
}

void NameEntryScreen::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128 && event.text.unicode != '\r') {
                playerName += static_cast<char>(event.text.unicode);
            }
            nameText.setString(playerName);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            if (!playerName.isEmpty()) {
                std::cout << "[DEBUG] Player Name Set: " << playerName.toAnsiString() << std::endl;
                game->setPlayerName(playerName.toAnsiString());
                game->changeState(Game::BATTLE);
            }
        }
    }
}

void NameEntryScreen:: resetName () {
    playerName = "";
    nameText.setString(""); 
}