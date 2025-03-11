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

const int INITIAL_GOLD = 3487;

const float MENU_buttonWidth = 400.0;
const float MENU_buttonHeight = 150.0;
const float MENU_spacing = 50.0;  
const float topLeftX = 950;
const float topLeftY = 550;

const int BACK_BUTTON_X = 20;
const int BACK_BUTTON_Y = 940;
const int HIGHSCORE_FONT = 44;
const int HIGHSCORE_TEXT_X = 1280;
const int HIGHSCORE_TEXT_Y = 280;
const int MAX_NUMBER_OF_SCORES_SHOWN = 10;

const int FONT_LARGE = 72;
const int NAMEENTRYSCREEN_X = 600;
const int NAMEENTRYSCREEN_Y = 400;

const int GAMEOVER_X = 650;
const int GAMEOVER_Y = 200;
const int GAMEOVER_SPACING = 100;
const int GAMEOVER_X_TITLE = 600;

void loadTexture(sf::Texture& texture, const std::string &filePath);
void loadFont(sf::Font& font, const std::string &filePath);

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const float PREDATOR_COLLISION_DELAY = 1.0f;
const int PREDATOR_MOVEMENT_FACTOR = 50;

const int GUNNER_ATTACK_POWER = 10;
const float GUNNER_ATTACK_SPEED = 1.5;
const float GUNNER_BULLET_SPEED = 600;

const int CANNONSHOOTER_ATTACK_POWER = 10;
const float CANNONSHOOTER_ATTACK_SPEED = 2.0;
const float CANNONSHOOTER_BULLET_SPEED = 500;

const int BASIC_PREDATOR_HEALTH = 100;
const float BASIC_PREDATOR_SPEED = 2.0f;

const std::string IMG_HIGHSCORE_SCREEN = "assets/highscore_screen.png";
const std::string IMG_BACK_BUTTON = "assets/back_button.png";
const std::string IMG_PREDATOR = "assets/predator.png";
const std::string IMG_BULLET = "assets/bullet.png";
const std::string IMG_CANNONBALL = "assets/cannonball.png";


#endif // CONSTANTS_HPP
