#ifndef BATTLEGROUND_HPP
#define BATTLEGROUND_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Grid.hpp"
#include "Spawner.hpp"
#include "Currency.hpp"
#include "Entity.hpp"
#include "Pirate.hpp"
#include "Gunner.hpp"
#include "CannonShooter.hpp"
#include "Bullet.hpp"
#include "GameOver.hpp"
#include <vector>

class BattleGround {
private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Grid grid;
    sf::Font font;
    sf::Text goldText;
    Spawner spawner;
    Currency currency;
    Game* game;
    std::vector<Bullet*> bullets;

    sf::Texture gunnerCardTexture, cannonShooterCardTexture;
    sf::Sprite gunnerCard, cannonShooterCard;

    sf::Texture pauseButtonTexture, resumeButtonTexture, restartButtonTexture, returnToMenuButtonTexture;
    sf::Sprite pauseButton, resumeButton, restartButton, quitButton;
    sf::RectangleShape pauseBackground;
    bool isPaused; 

    sf::Texture emptyWoodTexture, emptyWoodOtherTexture;
    sf::Sprite emptyWood, emptyWoodOther;

    sf::Text scoreText;  

    enum SelectedPirate { NONE, GUNNER, CANNON_SHOOTER };
    SelectedPirate selectedPirate;
public:
    BattleGround(Game* game);
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void handleInput(sf::RenderWindow &window); 
    bool placePirate(int x, int y, Pirate* pirate);
    void updateGoldText();
    void updateScoreText();
    static bool checkCollision(Entity* a, Entity* b);
};
#endif