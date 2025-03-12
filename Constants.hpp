#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
// 
const int CELL_SIZE = 120;
const int dCELL_SIZE = 120;

// spawner
const float INTITIAL_SPAWN_RATE = 12.0;
const float MAX_SPAWN_RATE = 2.0;
const float DECREAMENT_RATE = 0.2;
const int SPAWN_START_POSITION = 1920;

const int PREDATOR_RHINOMAN_HEALTH = 300;
const float PREDATOR_RHINOMAN_SPEED = 0.33;

const int PREDATOR_SNAKEMAN_HEALTH = 50;
const float PREDATOR_SNAKEMAN_SPEED = 2;

const int PREDATOR_ALIENMAN_HEALTH = 100;
const float PREDATOR_ALIENMAN_SPEED = 1;

const int INITIAL_GOLD = 300;

const float MENU_buttonWidth = 400.0;
const float MENU_buttonHeight = 150.0;
const float MENU_spacing = 50.0;  
const float topLeftX = 950;
const float topLeftY = 550;

const int BACK_BUTTON_X = 20;
const int BACK_BUTTON_Y = 940;
const int FONT_MEDIUM = 44;
const int HIGHSCORE_TEXT_X = 1280;
const int HIGHSCORE_TEXT_Y = 280;
const int MAX_NUMBER_OF_SCORES_SHOWN = 10;

const int FONT_LARGE = 72;
const int FONT_SMALL = 36;
const int NAMEENTRYSCREEN_X = 600;
const int NAMEENTRYSCREEN_Y = 400;

const int GAMEOVER_X = 650;
const int GAMEOVER_Y = 200;
const int GAMEOVER_SPACING = 100;
const int GAMEOVER_X_TITLE = 600;

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const float PREDATOR_COLLISION_DELAY = 2.5;
//const int PREDATOR_WAITING_TIME = 3;
const int PREDATOR_MOVEMENT_FACTOR = 50;

const int GUNNER_ATTACK_POWER = 13;
const float GUNNER_ATTACK_SPEED = 1.5;
const float GUNNER_BULLET_SPEED = 600;

const int CANNONSHOOTER_ATTACK_POWER = 50;
const float CANNONSHOOTER_ATTACK_SPEED = 6;
const float CANNONSHOOTER_BULLET_SPEED = 500;

const int BASIC_PREDATOR_HEALTH = 100;
const float BASIC_PREDATOR_SPEED = 2.0f;

const int GOLD_TEXT_X = 600;
const int GOLD_TEXT_Y = 20;

const int SCORE_TEXT_X = 1000;
const int SCORE_TEXT_Y = 20;

const int GUNNER_CARD_X = 100;
const int GUNNER_CARD_Y = 200;

const int CANNON_CARD_X = 100;
const int CANNON_CARD_Y = 400;

const int PAUSE_BTN_X = WINDOW_WIDTH - CELL_SIZE;
const int PAUSE_BTN_Y = 0;

const int PAUSE_START_X = 700;
const int PAUSE_START_Y = 250;
const int PAUSE_dY = 200;
const int PAUSE_SPACING = 50;

const int GRID_OFFSET_ROWS = 1;
const int GRID_OFFSET_COLS = 3;
const int GRID_ROWS = 7;
const int GRID_COLS = 13;

const int GUNNER_PRICE = 50;
const int CANNONSHOOTER_PRICE = 100;

const int GOLD_REWARD_AMOUNT = 50;
const int SCORE_REWARD_AMOUNT = 100;

const std::string IMG_HIGHSCORE_SCREEN = "assets/highscore_screen.png";
const std::string IMG_BACK_BUTTON = "assets/back_button.png";
const std::string IMG_BULLET = "assets/bullet.png";
const std::string IMG_CANNONBALL = "assets/cannonball.png";
const std::string IMG_BATTLEGROUND_GRID = "assets/battleground_background.png";
const std::string FONT_TTF_FILE = "assets/custom_font.ttf";
const std::string IMG_GUNNER_CARD = "assets/gunner_card.png";
const std::string IMG_CANNON_CARD = "assets/cannon_card.png";
const std::string IMG_PAUSE_BTN = "assets/pause_button.png";
const std::string IMG_RESUME_BTN = "assets/resume_button.png";
const std::string IMG_RESTART_BTN = "assets/restart_button.png";
const std::string IMG_RETURN_TO_MENU_BTN = "assets/quit_button_small.png";
const std::string IMG_GUNNER_SPRITE = "assets/gunner.png";
const std::string IMG_CANNONSHOOTER_SPRITE = "assets/cannonshooter.png";
const std::string IMG_EMPTY_WOOD1 = "assets/empty_wood.png";
const std::string IMG_EMPTY_WOOD2 = "assets/empty_wood_other.png";
const std::string IMG_PREDATOR_RHINOMAN = "assets/rhinoman.png";
const std::string IMG_PREDATOR_ALIENMAN = "assets/alienman.png";
const std::string IMG_PREDATOR_SNAKEMAN = "assets/snakeman.png";

void loadTexture(sf::Texture& texture, const std::string &filePath);
void loadFont(sf::Font& font, const std::string &filePath);

#endif // CONSTANTS_HPP
