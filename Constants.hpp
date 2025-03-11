#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
// 
const int CELL_SIZE = 120;
const int dCELL_SIZE = 120;

// spawner
const float INTITIAL_SPAWN_RATE = 7.0;
const float MAX_SPAWN_RATE = 2.0;
const float DECREAMENT_RATE = 0.2;
const int SPAWN_START_POSITION = 1920;

const int PREDATOR_HEALTH = 100;
const float PREDATOR_SPEED = 1.0;

const int INITIAL_GOLD = 100;

const float MENU_buttonWidth = 400.0;
const float MENU_buttonHeight = 150.0;
const float MENU_spacing = 50.0;  
const float topLeftX = 1000;
const float topLeftY = 550;

const int BACK_BUTTON_X = 20;
const int BACK_BUTTON_Y = 940;
const int HIGHSCORE_FONT = 44;
const int HIGHSCORE_TEXT_X = 1280;
const int HIGHSCORE_TEXT_Y = 280;
const int MAX_NUMBER_OF_SCORES_SHOWN = 10;

const int NAMEENTRYSCREEN_FONT = 72;
const int NAMEENTRYSCREEN_X = 600;
const int NAMEENTRYSCREEN_Y = 400;

void loadTexture(sf::Texture& texture, const std::string &filePath);
void loadFont(sf::Font& font, const std::string &filePath);

const std::string IMG_HIGHSCORE_SCREEN = "assets/highscore_screen.png";
const std::string IMG_BACK_BUTTON = "assets/back_button.png";

#endif // CONSTANTS_HPP
