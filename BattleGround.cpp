/// BattleGround.cpp - Implementation of BattleGround
#include "BattleGround.hpp"
#include "Gunner.hpp"
#include <iostream>

BattleGround::BattleGround(Game* game) : game(game), grid(6, 10), currency() {
    if (!backgroundTexture.loadFromFile("assets/battleground_background.png")) {
        std::cerr << "[ERROR] Failed to load battle background!" << std::endl;
    }
    background.setTexture(backgroundTexture);
    background.setScale(Game::scaleX, Game::scaleY);  // Scale background correctly

    cellWidth = 120;
    cellHeight = 120;

    if (!font.loadFromFile("assets/custom_font.ttf")) {
        std::cerr << "[ERROR] Failed to load font!" << std::endl;
    }

    // 🔹 Gold UI Scaling
    goldText.setFont(font);
    goldText.setCharacterSize(36 * Game::scaleX);  // Scale text size
    goldText.setFillColor(sf::Color::Yellow);
    goldText.setPosition(800 * Game::scaleX, 20 * Game::scaleY);
    updateGoldText();

    // 🔹 Load Pirate Selection Cards
    if (!gunnerCardTexture.loadFromFile("assets/gunner_card.png") ||
        !cannonShooterCardTexture.loadFromFile("assets/cannon_card.png")) {
        std::cerr << "[ERROR] Failed to load pirate cards!" << std::endl;
    } else {
        std::cout << "[DEBUG] Pirate Cards Loaded Successfully!" << std::endl;
    }

    // 🔹 Scale and Position Pirate Cards Correctly
    gunnerCard.setTexture(gunnerCardTexture);
    cannonShooterCard.setTexture(cannonShooterCardTexture);

    gunnerCard.setScale(Game::scaleX, Game::scaleY);
    cannonShooterCard.setScale(Game::scaleX, Game::scaleY);

    gunnerCard.setPosition(50 * Game::scaleX, 200 * Game::scaleY);  // Adjust position with scaling
    cannonShooterCard.setPosition(50 * Game::scaleX, 400 * Game::scaleY);

    selectedPirate = NONE;  // No pirate selected initially
}

void BattleGround::render(sf::RenderWindow &window) {
    window.draw(background);

    // 🔹 Draw Grid with Scaling
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 10; col++) {
            sf::RectangleShape cell(sf::Vector2f(cellWidth * Game::scaleX, cellHeight * Game::scaleY));
            cell.setPosition((400 + col * cellWidth) * Game::scaleX, (200 + row * cellHeight) * Game::scaleY);
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black);
            cell.setFillColor(sf::Color(139, 69, 19));  // Wood color
            window.draw(cell);
        }
    }

    // 🔹 Draw Gold UI with Scaling
    goldText.setPosition(800 * Game::scaleX, 20 * Game::scaleY);
    goldText.setCharacterSize(36 * Game::scaleX);
    window.draw(goldText);

    // 🔹 Draw Pirate Selection Cards
    gunnerCard.setScale(Game::scaleX, Game::scaleY);  // Scale cards properly
    cannonShooterCard.setScale(Game::scaleX, Game::scaleY);

    gunnerCard.setPosition(50 * Game::scaleX, 200 * Game::scaleY);  // Adjust position
    cannonShooterCard.setPosition(50 * Game::scaleX, 400 * Game::scaleY);

    window.draw(gunnerCard);
    window.draw(cannonShooterCard);

    // 🔹 Draw Pirates and Predators
    grid.render(window);
    spawner.render(window);

    // Draw Bullets
    for (Bullet* bullet : bullets) {
        window.draw(bullet->getSprite());  // 🔹 Draw each bullet
    }
}


void BattleGround::update(float deltaTime) {
    spawner.update(deltaTime);
    grid.update();

    // std::cout << "[DEBUG] Bullets in game: " << bullets.size() << std::endl;  // Print bullet count
    
    // Handle Pirate Attacks
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 10; ++x) {
            Pirate* pirate = dynamic_cast<Pirate*>(grid.getEntity(x, y));
            if (pirate) {
                Bullet* newBullet = pirate->fireBullet(deltaTime);
                if (newBullet) {
                    bullets.push_back(newBullet);
                    std::cout << "[DEBUG] Bullet added to game. Total bullets: " << bullets.size() << std::endl;
                }
            }
        }
    }

    // Move Bullets & Check for Collision
    for (auto it = bullets.begin(); it != bullets.end();) {
        Bullet* bullet = *it;
        bullet->move(deltaTime);

        bool bulletHit = false;
        for (Predator* enemy : spawner.getEnemies()) {
            if (Collision::checkCollision(bullet, enemy)) {
                enemy->takeDamage(bullet->getDamage());
                delete bullet;
                it = bullets.erase(it);
                bulletHit = true;
                break;
            }
        }
        if (!bulletHit) {
            ++it;
        }
    }

    // Remove Dead Predators
    for (auto it = spawner.getEnemies().begin(); it != spawner.getEnemies().end();) {
        Predator* enemy = *it;
        if (enemy->isDefeated()) {
            delete enemy;
            it = spawner.getEnemies().erase(it);
            currency.addGold(10);  // Reward player for killing a predator
            updateGoldText();
        } else {
            ++it;
        }
    }
}

void BattleGround::updateBullets(float deltaTime) {
    for (auto it = bullets.begin(); it != bullets.end();) {
        Bullet* bullet = *it;
        bullet->move(deltaTime);
        
        bool bulletHit = false;
        for (Predator* enemy : spawner.getEnemies()) {
            if (Collision::checkCollision(bullet, enemy)) {
                enemy->takeDamage(bullet->getDamage());
                delete bullet;
                it = bullets.erase(it);
                bulletHit = true;
                break;
            }
        }
        
        if (!bulletHit) {
            ++it;
        }
    }
}

bool BattleGround::placePirate(int x, int y, Pirate* pirate) {
    if (currency.spendGold(20)) { // Deduct cost for placing a pirate
        updateGoldText();
        return grid.placePirate(x, y, pirate);
    }
    return false;
}

void BattleGround::updateGoldText() {
    goldText.setString("Gold: " + std::to_string(currency.getGold()));
}

void BattleGround::handleInput(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // 🔹 Check for Single Click on Pirate Cards
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            // 🔹 Debug Click Position
            std::cout << "[DEBUG] Mouse Clicked at: X=" << worldPos.x << ", Y=" << worldPos.y << std::endl;

            // 🔹 Check for Card Selection
            if (gunnerCard.getGlobalBounds().contains(worldPos)) {
                selectedPirate = GUNNER;
                std::cout << "[DEBUG] Gunner Selected!" << std::endl;
                return;
            } else if (cannonShooterCard.getGlobalBounds().contains(worldPos)) {
                selectedPirate = CANNON_SHOOTER;
                std::cout << "[DEBUG] Cannon Shooter Selected!" << std::endl;
                return;
            }

            // 🔹 Convert Click to Grid Coordinates
            int col = (worldPos.x - 400) / cellWidth;
            int row = (worldPos.y - 200) / cellHeight;

            if (col >= 0 && col < 10 && row >= 0 && row < 6) {
                std::cout << "[DEBUG] Click Detected on Grid Cell: (" << col << ", " << row << ")" << std::endl;

                if (selectedPirate != NONE) {
                    if (currency.getGold() >= 50) {
                        Pirate* newPirate = nullptr;

                        if (selectedPirate == GUNNER) {
                            newPirate = new Gunner("assets/gunner.png", col * cellWidth + 400, row * cellHeight + 200);
                        } else if (selectedPirate == CANNON_SHOOTER) {
                            newPirate = new CannonShooter("assets/cannonshooter.png", col * cellWidth + 400, row * cellHeight + 200);
                        }

                        if (newPirate) {
                            bool placed = grid.placePirate(col, row, newPirate);
                            if (placed) {
                                std::cout << "[DEBUG] Pirate Placed at (" << col << ", " << row << ")" << std::endl;
                                currency.spendGold(50);
                                updateGoldText();
                                selectedPirate = NONE;  // Reset selection
                            } else {
                                std::cout << "[DEBUG] Cell Occupied! Could Not Place Pirate." << std::endl;
                                delete newPirate;
                            }
                        }
                    } else {
                        std::cout << "[DEBUG] Not Enough Gold!" << std::endl;
                    }
                }
            }
        }
    }
}
