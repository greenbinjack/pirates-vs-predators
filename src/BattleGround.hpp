#ifndef BATTLEGROUND_HPP
#define BATTLEGROUND_HPP

#include "Bullet.hpp"
#include "CannonShooter.hpp"
#include "Currency.hpp"
#include "Entity.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "Grid.hpp"
#include "Gunner.hpp"
#include "Pirate.hpp"
#include "Spawner.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

class BattleGround
{
  private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Grid grid;
    sf::Font font;
    sf::Text goldText;
    Spawner spawner;
    Currency currency;
    Game *game;
    std::vector<Bullet *> bullets;

    sf::Texture gunnerCardTexture, cannonShooterCardTexture;
    sf::Sprite gunnerCard, cannonShooterCard;

    sf::Texture pauseButtonTexture, resumeButtonTexture, restartButtonTexture, returnToMenuButtonTexture;
    sf::Sprite pauseButton, resumeButton, restartButton, quitButton;
    sf::RectangleShape pauseBackground;
    bool isPaused;

    sf::Texture emptyWoodTexture, emptyWoodOtherTexture;
    sf::Sprite emptyWood, emptyWoodOther;

    sf::Texture treasureChestTexture;
    sf::Sprite treasureChest;

    sf::Text scoreText;

    sf::Texture gameLogoTexture;
    sf::Sprite gameLogo;

    enum SelectedPirate
    {
        NONE,
        GUNNER,
        CANNON_SHOOTER
    };
    SelectedPirate selectedPirate;

  public:
    BattleGround (Game *game);
    void update (float deltaTime);
    void render (sf::RenderWindow &window);
    void handleInput (sf::RenderWindow &window);
    void updateGoldText ();
    void updateScoreText ();
    static bool checkCollision (Entity *a, Entity *b);
};
#endif