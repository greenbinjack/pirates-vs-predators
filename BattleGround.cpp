#include "BattleGround.hpp"
#include "Gunner.hpp"
#include <iostream>

BattleGround::BattleGround(Game* game) : game(game), grid(7, 13), currency() {
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

    scoreText.setFont(font);
    scoreText.setCharacterSize(36 * Game::scaleX);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(1000 * Game::scaleX, 20 * Game::scaleY);
    updateScoreText();

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

    // Load Pause Button
    if (!pauseButtonTexture.loadFromFile("assets/pause_button.png")) {
        std::cerr << "[ERROR] Failed to load Pause Button!" << std::endl;
    }
    pauseButton.setTexture(pauseButtonTexture);
    pauseButton.setPosition(1700 * Game::scaleX, 20 * Game::scaleY);
    pauseButton.setScale(Game::scaleX, Game::scaleY);

    // Load Pause Menu Buttons
    if (!resumeButtonTexture.loadFromFile("assets/resume_button.png") ||
        !restartButtonTexture.loadFromFile("assets/restart_button.png") ||
        !quitButtonTexture.loadFromFile("assets/quit_button_small.png")) {
        std::cerr << "[ERROR] Failed to load Pause Menu Buttons!" << std::endl;
    }

    resumeButton.setTexture(resumeButtonTexture);
    restartButton.setTexture(restartButtonTexture);
    quitButton.setTexture(quitButtonTexture);

    // Position Buttons in the Center of the Screen
    resumeButton.setPosition(800 * Game::scaleX, 400 * Game::scaleY);
    restartButton.setPosition(800 * Game::scaleX, 550 * Game::scaleY);
    quitButton.setPosition(800 * Game::scaleX, 700 * Game::scaleY);

    resumeButton.setScale(Game::scaleX, Game::scaleY);
    restartButton.setScale(Game::scaleX, Game::scaleY);
    quitButton.setScale(Game::scaleX, Game::scaleY);

    // Create Pause Background
    pauseBackground.setSize(sf::Vector2f(600 * Game::scaleX, 400 * Game::scaleY));
    pauseBackground.setFillColor(sf::Color(0, 0, 0, 150)); // Transparent Black
    pauseBackground.setPosition(660 * Game::scaleX, 300 * Game::scaleY);

    isPaused = false;
     
}

void BattleGround::render(sf::RenderWindow &window) {
    if (isPaused) {
        // Draw Pause Background and Buttons
        window.draw(pauseBackground);
        window.draw(resumeButton);
        window.draw(restartButton);
        window.draw(quitButton);
    } else {
        window.draw(background);

        // Draw Grid with Scaling
        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 10; col++) {
                sf::RectangleShape cell(sf::Vector2f(cellWidth * Game::scaleX, cellHeight * Game::scaleY));
                cell.setPosition((360 + col * cellWidth) * Game::scaleX, (120 + row * cellHeight) * Game::scaleY);
                cell.setFillColor(sf::Color::Transparent);
                // cell.setOutlineThickness(0.5);
                // cell.setOutlineColor(sf::Color::Black);
                window.draw(cell);
            }
        }

        // Draw Gold UI
        window.draw(goldText);
        window.draw (scoreText);

        // Draw Pirate Cards
        window.draw(gunnerCard);
        window.draw(cannonShooterCard);

        // Draw Pirates and Predators
        grid.render(window);
        spawner.render(window);

        // Draw Bullets
        for (Bullet* bullet : bullets) {
            window.draw(bullet->getSprite());
        }

        // Draw Pause Button
        window.draw(pauseButton);
    }
}

void BattleGround::update(float deltaTime) {
    if (isPaused) return; 
    spawner.update(deltaTime);
    grid.update();

    for (Predator* enemy : spawner.getEnemies()) {
        if (enemy->getPosition().x <= 360) {
            std::cout << "[DEBUG] Predator reached base! GAME OVER!\n";
            game->changeState(Game::GAME_OVER);
            return;  
        }
    }
    // std::cout << "[DEBUG] Bullets in game: " << bullets.size() << std::endl;  // Print bullet count
    
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
                int col = (worldPos.x - 360) / cellWidth;
                int row = (worldPos.y - 120) / cellHeight;

                if (col >= 0 && col < 10 && row >= 0 && row < 7 && selectedPirate != NONE) {
                    if (currency.getGold() >= 50) {
                        Pirate* newPirate = nullptr;

                        if (selectedPirate == GUNNER) {
                            newPirate = new Gunner("assets/gunner.png", col * cellWidth + 360, row * cellHeight + 120);
                        } else if (selectedPirate == CANNON_SHOOTER) {
                            newPirate = new CannonShooter("assets/cannonshooter.png", col * cellWidth + 360, row * cellHeight + 120);
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
