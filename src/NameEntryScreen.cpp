#include "NameEntryScreen.hpp"
#include "Game.hpp"
#include "Constants.hpp"
#include <iostream>

NameEntryScreen::NameEntryScreen ()
{
    loadFont (font, FONT_TTF_FILE);
    promptText.setFont (font);
    promptText.setCharacterSize (FONT_LARGE);
    promptText.setFillColor (sf::Color::White);
    promptText.setString ("Enter Your Name:");
    promptText.setPosition (NAMEENTRYSCREEN_X, NAMEENTRYSCREEN_Y);

    nameText.setFont (font);
    nameText.setCharacterSize (FONT_LARGE);
    nameText.setFillColor (sf::Color::Yellow);
    nameText.setPosition (NAMEENTRYSCREEN_X, NAMEENTRYSCREEN_Y + MENU_spacing + MENU_spacing);
}

void
NameEntryScreen::display (sf::RenderWindow &window)
{
    window.clear ();
    window.draw (promptText);
    window.draw (nameText);
    window.display ();
}

void
NameEntryScreen::handleInput (sf::RenderWindow &window, Game &game)
{
    sf::Event event;
    while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                {
                    window.close ();
                }

            if (event.type == sf::Event::TextEntered)
                {
                    char inputChar = static_cast<char> (event.text.unicode);
                    if (std::isalnum (inputChar))
                        {
                            playerName += static_cast<char> (std::toupper (inputChar));
                        }
                    else if (inputChar == 8 && !playerName.isEmpty ())
                        {
                            playerName.erase (playerName.getSize () - 1, 1);
                        }
                    nameText.setString (playerName);
                }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                {
                    if (!playerName.isEmpty ())
                        {
                            std::cout << "[DEBUG] Player Name Set: " << playerName.toAnsiString () << std::endl;
                            game.setPlayerName (playerName.toAnsiString ());
                            game.changeState (Game::BATTLE);
                        }
                }
        }
}

void
NameEntryScreen::resetName ()
{
    playerName = "";
    nameText.setString ("");
}