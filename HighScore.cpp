/// HighScore.cpp - Implementation of HighScore Screen
#include "HighScore.hpp"
#include "Game.hpp"  // Add this line to access Game functions
#include <iostream>
#include <fstream>
#include <algorithm>

HighScore::HighScore() {
    loadScores();
    if (!backgroundTexture.loadFromFile("assets/highscore_screen.png")) {
        std::cerr << "Error loading highscore background!" << std::endl;
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
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setPosition(100, 150);
}

void HighScore::loadScores() {
    std::ifstream file("assets/highscores.txt");
    if (!file) {
        std::cerr << "Error loading highscores file!" << std::endl;
        return;
    }
    int score;
    scores.clear();
    while (file >> score) {
        scores.push_back(score);
    }
    file.close();
    std::sort(scores.rbegin(), scores.rend()); // Sort in descending order
    updateHighScoreText();
}

void HighScore::saveScores() {
    std::ofstream file("assets/highscores.txt");
    for (size_t i = 0; i < std::min(scores.size(), size_t(5)); i++) {
        file << scores[i] << std::endl;
    }
    file.close();
}

void HighScore::addNewScore(int score) {
    scores.push_back(score);
    std::sort(scores.rbegin(), scores.rend()); // Keep highest at the top
    while (scores.size() > 5) {
        scores.pop_back(); // Keep only top 5
    }
    saveScores();
    updateHighScoreText();
}

void HighScore::updateHighScoreText() {
    std::string content = "High Scores:\n";
    for (size_t i = 0; i < scores.size(); i++) {
        content += std::to_string(i + 1) + ". " + std::to_string(scores[i]) + "\n";
    }
    highScoreText.setString(content);
}

void HighScore::display(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(highScoreText);
    window.draw(backButton);
}

void HighScore::handleInput(sf::RenderWindow &window, Game &game) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      if (backButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
          game.changeState(Game::MENU);
      }
  }
}
