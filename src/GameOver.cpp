#include "Constants.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include <iostream>

GameOver::GameOver ()
{
    loadTexture (menuButtonTexture, IMG_RETURN_TO_MENU_BTN);
    menuButton.setTexture (menuButtonTexture);
    menuButton.setPosition (GAMEOVER_X, GAMEOVER_Y + 4 * GAMEOVER_SPACING);

    loadFont (font, FONT_TTF_FILE);

    gameOverText.setFont (font);
    gameOverText.setString ("Game Over");
    gameOverText.setCharacterSize (FONT_LARGE + FONT_LARGE);
    gameOverText.setFillColor (sf::Color::White);
    gameOverText.setPosition (GAMEOVER_X_TITLE, GAMEOVER_Y);

    finalScoreText.setFont (font);
    finalScoreText.setCharacterSize (FONT_LARGE);
    finalScoreText.setFillColor (sf::Color::Red);
    finalScoreText.setPosition (GAMEOVER_X, GAMEOVER_Y + 2 * GAMEOVER_SPACING);

    playerNameText.setFont (font);
    playerNameText.setCharacterSize (FONT_LARGE);
    playerNameText.setFillColor (sf::Color::Yellow);
    playerNameText.setPosition (GAMEOVER_X, GAMEOVER_Y + 3 * GAMEOVER_SPACING);
}

void
GameOver::display (sf::RenderWindow &window)
{
    window.clear ();
    window.draw (gameOverText);
    window.draw (finalScoreText);
    window.draw (menuButton);
    window.draw (playerNameText);
    window.display ();
}

void
GameOver::handleInput (sf::RenderWindow &window, Game &game)
{
    sf::Event event;
    while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                {
                    window.close ();
                }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition (window);
                    sf::Vector2f worldPos = window.mapPixelToCoords (pixelPos);

                    if (menuButton.getGlobalBounds ().contains (worldPos))
                        {
                            std::cout << "[DEBUG] Menu Button Clicked! Returning to Menu." << std::endl;
                            game.saveScore ();
                            game.restartGame (true);
                        }
                }
        }
}

void
GameOver::updateFinalScore (int score, const std::string &name)
{
    finalScoreText.setString ("Final Score: " + std::to_string (score));
    playerNameText.setString ("Player: " + name);
}
