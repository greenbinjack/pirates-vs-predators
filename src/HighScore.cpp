#include "Constants.hpp"
#include "Game.hpp"
#include "HighScore.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

HighScore::HighScore ()
{
    loadScores ();

    loadTexture (backgroundTexture, IMG_HIGHSCORE_SCREEN);
    background.setTexture (backgroundTexture);

    loadTexture (backButtonTexture, IMG_BACK_BUTTON);
    backButton.setTexture (backButtonTexture);
    backButton.setPosition (BACK_BUTTON_X, BACK_BUTTON_Y);

    loadFont (font, FONT_TTF_FILE);
    highScoreText.setFont (font);
    highScoreText.setCharacterSize (FONT_MEDIUM);
    highScoreText.setFillColor (sf::Color::Black);
    highScoreText.setPosition (HIGHSCORE_TEXT_X, HIGHSCORE_TEXT_Y);
}

void
HighScore::loadScores ()
{
    std::ifstream file (FILE_HIGHSCORE);
    try
        {
            if (!file)
                {
                    throw std::runtime_error ("Failed to load highscores.txt file: ");
                }
        }
    catch (const std::exception &e)
        {
            std::cerr << "[ERROR] " << e.what () << std::endl;
            exit (0);
        }

    scores.clear ();

    std::string name;
    int score;
    while (file >> score >> name)
        {
            scores.push_back ({ score, name });
        }
    file.close ();

    sort (scores.rbegin (), scores.rend ());
    updateHighScoreText ();
}

void
HighScore::saveScores ()
{
    std::ofstream file (FILE_HIGHSCORE);
    for (size_t i = 0; i < std::min (scores.size (), size_t (MAX_NUMBER_OF_SCORES_SHOWN)); i++)
        {
            file << scores[i].first << ' ' << scores[i].second << std::endl;
        }
    file.close ();
}

void
HighScore::addNewScore (int score, const std::string &name)
{
    scores.push_back ({ score, name });
    std::sort (scores.rbegin (), scores.rend ());

    while (scores.size () > MAX_NUMBER_OF_SCORES_SHOWN)
        {
            scores.pop_back ();
        }

    saveScores ();
    updateHighScoreText ();
}

void
HighScore::updateHighScoreText ()
{
    std::string content = "";
    for (size_t i = 0; i < scores.size (); i++)
        {
            content += std::to_string (i + 1) + ". " + scores[i].second + " - " + std::to_string (scores[i].first) + "\n";
        }
    highScoreText.setString (content);
}

void
HighScore::display (sf::RenderWindow &window)
{
    window.draw (background);
    window.draw (highScoreText);
    window.draw (backButton);
}

void
HighScore::handleInput (sf::RenderWindow &window, Game &game)
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
