#include "BattleGround.hpp"
#include "Gunner.hpp"
#include "Constants.hpp"
#include <iostream>

BattleGround::BattleGround(Game* game) : game(game), grid(GRID_ROWS, GRID_COLS), currency() {
    loadTexture (backgroundTexture, IMG_BATTLEGROUND_GRID);
    background.setTexture(backgroundTexture);

    loadFont (font, FONT_TTF_FILE);

    goldText.setFont(font);
    goldText.setCharacterSize(FONT_SMALL);  
    goldText.setFillColor(sf::Color::Yellow);
    goldText.setPosition(GOLD_TEXT_X, GOLD_TEXT_Y);
    updateGoldText();

    scoreText.setFont(font);
    scoreText.setCharacterSize(FONT_SMALL);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(SCORE_TEXT_X, SCORE_TEXT_Y);
    updateScoreText();

    loadTexture (gunnerCardTexture, IMG_GUNNER_CARD);
    loadTexture (cannonShooterCardTexture, IMG_CANNON_CARD);
    gunnerCard.setTexture(gunnerCardTexture);
    cannonShooterCard.setTexture(cannonShooterCardTexture);
    gunnerCard.setPosition(GUNNER_CARD_X, GUNNER_CARD_Y);  
    cannonShooterCard.setPosition(CANNON_CARD_X, CANNON_CARD_Y);

    selectedPirate = NONE; 

    /** 
     * PAUSE PHASE
     */
    loadTexture (pauseButtonTexture, IMG_PAUSE_BTN);
    pauseButton.setTexture(pauseButtonTexture);
    pauseButton.setPosition(PAUSE_BTN_X, PAUSE_BTN_Y);

    loadTexture (resumeButtonTexture, IMG_RESUME_BTN);
    loadTexture (restartButtonTexture, IMG_RESTART_BTN);
    loadTexture (returnToMenuButtonTexture, IMG_RETURN_TO_MENU_BTN);
    resumeButton.setTexture(resumeButtonTexture);
    restartButton.setTexture(restartButtonTexture);
    quitButton.setTexture(returnToMenuButtonTexture);

    resumeButton.setPosition(PAUSE_START_X, PAUSE_START_Y);
    restartButton.setPosition(PAUSE_START_X, PAUSE_START_Y + PAUSE_dY);
    quitButton.setPosition(PAUSE_START_X, PAUSE_START_Y + 2 * PAUSE_dY);
    pauseBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Transparent Black

    isPaused = false;
}

void BattleGround::render(sf::RenderWindow &window) {
    switch (isPaused) {
    case true:
        window.draw(pauseBackground);
        window.draw(resumeButton);
        window.draw(restartButton);
        window.draw(quitButton);
        break;
    case false:
        window.draw(background);
        window.draw(goldText);
        window.draw (scoreText);
        window.draw(gunnerCard);
        window.draw(cannonShooterCard);
        grid.render(window);
        spawner.render(window);
        for (Bullet* bullet : bullets) {
            bullet->render (window);
        }
        window.draw(pauseButton);
        break;
    }
}

void BattleGround::update(float deltaTime) {
    if (isPaused) return; 
    spawner.update(deltaTime);

    for (Predator* enemy : spawner.getEnemies()) {
        if (enemy->getPosition().x <= 360) {
            std::cout << "[DEBUG] Predator reached base! GAME OVER!\n";
            game->changeState(Game::GAME_OVER);
            return;  
        }
    }
    // std::cout << "[DEBUG] Bullets in game: " << bullets.size() << std::endl;  // Print bullet count

    // ✅ Check for predator-pirate collisions
    for (Predator* enemy : spawner.getEnemies()) {
        int col = (enemy->getPosition().x - 360) / CELL_SIZE;  // ✅ Convert x position to grid column
        int row = (enemy->getPosition().y - 120) / CELL_SIZE;  // ✅ Convert y position to grid row

        if (col >= 0 && col < 10 && row >= 0 && row < 7) {  // ✅ Ensure valid grid position
            Pirate* pirate = dynamic_cast<Pirate*>(grid.getEntity(col, row));
            if (pirate) {
                std::cout << "[DEBUG] Predator collided with pirate at (" << col << ", " << row << ")\n";
                grid.removeEntity(col, row);  // ✅ Remove the pirate
                enemy->pauseMovement();  // ✅ Pause predator for 1 second
            }
        }

        if (enemy->getPosition().x <= 360) {
            std::cout << "[DEBUG] Predator reached base! GAME OVER!\n";
            game->changeState(Game::GAME_OVER);
            return;  
        }
    }
    
    // Handle Pirate Attacks
    for (int y = 0; y < 7; ++y) {
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
        bullet->update(deltaTime);

        bool bulletHit = false;
        for (Predator* enemy : spawner.getEnemies()) {
            if (checkCollision(bullet, enemy)) {
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
            game->addScore(100);  // ✅ Increase score by 100
            updateScoreText();
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
        bullet->update(deltaTime);
        
        bool bulletHit = false;
        for (Predator* enemy : spawner.getEnemies()) {
            if (checkCollision(bullet, enemy)) {
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

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            if (!isPaused) {
                // Check Pause Button Click
                if (pauseButton.getGlobalBounds().contains(worldPos)) {
                    isPaused = true;
                    std::cout << "[DEBUG] Game Paused!" << std::endl;
                    return;
                }

                // Check for Pirate Selection
                if (gunnerCard.getGlobalBounds().contains(worldPos)) {
                    selectedPirate = GUNNER;
                    std::cout << "[DEBUG] Gunner Selected!" << std::endl;
                    return;
                } else if (cannonShooterCard.getGlobalBounds().contains(worldPos)) {
                    selectedPirate = CANNON_SHOOTER;
                    std::cout << "[DEBUG] Cannon Shooter Selected!" << std::endl;
                    return;
                }

                // Convert Click to Grid Coordinates
                int col = (worldPos.x - 360) / CELL_SIZE;
                int row = (worldPos.y - 120) / CELL_SIZE;

                if (col >= 0 && col < 10 && row >= 0 && row < 7 && selectedPirate != NONE) {
                    if (currency.getGold() >= 50) {
                        Pirate* newPirate = nullptr;

                        if (selectedPirate == GUNNER) {
                            newPirate = new Gunner("assets/gunner.png", col * CELL_SIZE + 360, row * CELL_SIZE + 120);
                        } else if (selectedPirate == CANNON_SHOOTER) {
                            newPirate = new CannonShooter("assets/cannonshooter.png", col * CELL_SIZE + 360, row * CELL_SIZE + 120);
                        }

                        if (newPirate) {
                            bool placed = grid.placePirate(col, row, newPirate);
                            if (placed) {
                                std::cout << "[DEBUG] Pirate Placed at (" << col << ", " << row << ")" << std::endl;
                                currency.spendGold(50);
                                updateGoldText();
                            } else {
                                std::cout << "[DEBUG] Cell Occupied! Could Not Place Pirate." << std::endl;
                                delete newPirate;
                            }
                        }
                        selectedPirate = NONE;  // Reset selection
                    } else {
                        std::cout << "[DEBUG] Not Enough Gold!" << std::endl;
                    }
                }
            } else {
                // **Handle Pause Menu Button Clicks**
                if (resumeButton.getGlobalBounds().contains(worldPos)) {
                    isPaused = false;
                    std::cout << "[DEBUG] Game Resumed!" << std::endl;
                } 
                else if (restartButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "[DEBUG] Restarting Game!" << std::endl;
                    game->restartGame(0);  // o for BATTLE
                } 
                else if (quitButton.getGlobalBounds().contains(worldPos)) {
                    std::cout << "[DEBUG] Quitting to Menu!" << std::endl;
                    game->restartGame(1); // 1 for MENU
                    return;
                }
            }
        }
    }
}

void BattleGround::updateScoreText() {
    scoreText.setString("Score: " + std::to_string(game->getScore()));
}

bool BattleGround::checkCollision(Entity* a, Entity* b) {
    return a->getBounds().intersects(b->getBounds());
}