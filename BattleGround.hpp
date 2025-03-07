/// BattleGround.hpp - Manages the Game Battle Area
#ifndef BATTLEGROUND_HPP
#define BATTLEGROUND_HPP
#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Spawner.hpp"
#include "Currency.hpp"
#include "Pirate.hpp"
#include "Gunner.hpp"
#include "CannonShooter.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include <vector>

class BattleGround {
private:
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Grid grid;
    Spawner spawner;
    Currency currency;
    Game* game;
    sf::Font font;
    sf::Text goldText;
    std::vector<Bullet*> bullets;
    int cellWidth;
    int cellHeight;

    sf::Texture gunnerCardTexture, cannonShooterCardTexture;
    sf::Sprite gunnerCard, cannonShooterCard;

    // 🔹 Store the selected pirate type
    enum SelectedPirate { NONE, GUNNER, CANNON_SHOOTER };
    SelectedPirate selectedPirate;
public:
    BattleGround(Game* game);
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void handleInput(sf::RenderWindow &window);  // 🔹 Declare handleInput()
    bool placePirate(int x, int y, Pirate* pirate);
    void updateGoldText();
    void updateBullets(float deltaTime);
};
#endif