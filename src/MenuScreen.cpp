#include "MenuScreen.hpp"
#include "Constants.hpp"
#include "Game.hpp"
#include <iostream>

MenuScreen::MenuScreen ()
{
    loadTexture (backgroundTexture, IMG_MENUSCREEN);
    background.setTexture (backgroundTexture);
    
    loadTexture (startButtonTexture, IMG_START_BUTTON);
    loadTexture (instructionsButtonTexture, IMG_INSTRUCTION_BUTTON);
    loadTexture (quitButtonTexture, IMG_QUIT_BUTTON);
    loadTexture (highscoreButtonTexture, IMG_HIGHSCORE_BUTTON);


    startButton.setTexture (startButtonTexture);
    instructionsButton.setTexture (instructionsButtonTexture);
    quitButton.setTexture (quitButtonTexture);
    highscoreButton.setTexture (highscoreButtonTexture);

    startButton.setPosition (topLeftX, topLeftY);                                                                     // Top-left
    instructionsButton.setPosition (topLeftX + MENU_buttonWidth + MENU_spacing, topLeftY);                            // Top-right
    highscoreButton.setPosition (topLeftX, topLeftY + MENU_buttonHeight + MENU_spacing);                              // Bottom-left
    quitButton.setPosition (topLeftX + MENU_buttonWidth + MENU_spacing, topLeftY + MENU_buttonHeight + MENU_spacing); // Bottom-right
}

void
MenuScreen::display (sf::RenderWindow &window)
{
    window.draw (background);
    window.draw (startButton);
    window.draw (instructionsButton);
    window.draw (highscoreButton);
    window.draw (quitButton);
}

void
MenuScreen::handleInput (sf::RenderWindow &window, Game &game)
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

                    std::cout << "[DEBUG] Mouse Clicked at: X=" << worldPos.x << ", Y=" << worldPos.y << std::endl;

                    if (startButton.getGlobalBounds ().contains (worldPos))
                        {
                            std::cout << "[DEBUG] Start Button Clicked!" << std::endl;
                            game.changeState (Game::ENTER_NAME);
                        }
                    else if (instructionsButton.getGlobalBounds ().contains (worldPos))
                        {
                            std::cout << "[DEBUG] Instructions Button Clicked!" << std::endl;
                            game.changeState (Game::INSTRUCTIONS);
                        }
                    else if (highscoreButton.getGlobalBounds ().contains (worldPos))
                        {
                            std::cout << "[DEBUG] Highscore Button Clicked!" << std::endl;
                            game.changeState (Game::HIGHSCORE);
                        }
                    else if (quitButton.getGlobalBounds ().contains (worldPos))
                        {
                            std::cout << "[DEBUG] Quit Button Clicked!" << std::endl;
                            window.close ();
                        }
                }
        }
}
