#include "BattleGround.hpp"
#include "Constants.hpp"
#include "Gunner.hpp"
#include <iostream>

BattleGround::BattleGround (Game *game) : game (game), grid (GRID_ROWS, GRID_COLS), currency ()
{
    loadTexture (backgroundTexture, IMG_BATTLEGROUND_GRID);
    background.setTexture (backgroundTexture);

    loadFont (font, FONT_TTF_FILE);

    loadTexture (emptyWoodTexture, IMG_EMPTY_WOOD1);
    emptyWood.setTexture (emptyWoodTexture);
    emptyWood.setPosition (GOLD_TEXT_X, GOLD_TEXT_Y - 10);

    loadTexture (treasureChestTexture, IMG_TREASURE_CHEST);
    treasureChest.setTexture (treasureChestTexture);
    treasureChest.setPosition (GOLD_TEXT_X + MENU_spacing, GOLD_TEXT_Y);

    goldText.setFont (font);
    goldText.setCharacterSize (FONT_MEDIUM);
    goldText.setFillColor (sf::Color::Yellow);
    goldText.setPosition (GOLD_TEXT_X + GOLD_TEXT_SPACING + MENU_spacing, GOLD_TEXT_Y);
    updateGoldText ();

    loadTexture (emptyWoodOtherTexture, IMG_EMPTY_WOOD2);
    emptyWoodOther.setTexture (emptyWoodOtherTexture);
    emptyWoodOther.setPosition (SCORE_TEXT_X - MENU_spacing, SCORE_TEXT_Y - 10);
    scoreText.setFont (font);
    scoreText.setCharacterSize (FONT_MEDIUM);
    scoreText.setFillColor (sf::Color::White);
    scoreText.setPosition (SCORE_TEXT_X, SCORE_TEXT_Y);
    game->resetScore ();
    updateScoreText ();

    loadTexture (gameLogoTexture, IMG_GAME_LOGO);
    gameLogo.setTexture (gameLogoTexture);
    gameLogo.setPosition (GAME_LOGO_X, GAME_LOGO_Y);

    loadTexture (gunnerCardTexture, IMG_GUNNER_CARD);
    loadTexture (cannonShooterCardTexture, IMG_CANNON_CARD);
    gunnerCard.setTexture (gunnerCardTexture);
    cannonShooterCard.setTexture (cannonShooterCardTexture);
    gunnerCard.setPosition (GUNNER_CARD_X, GUNNER_CARD_Y);
    cannonShooterCard.setPosition (CANNON_CARD_X, CANNON_CARD_Y);

    selectedPirate = NONE;

    /**
     * PAUSE PHASE
     */
    loadTexture (pauseButtonTexture, IMG_PAUSE_BTN);
    pauseButton.setTexture (pauseButtonTexture);
    pauseButton.setPosition (PAUSE_BTN_X, PAUSE_BTN_Y);

    loadTexture (resumeButtonTexture, IMG_RESUME_BTN);
    loadTexture (restartButtonTexture, IMG_RESTART_BTN);
    loadTexture (returnToMenuButtonTexture, IMG_RETURN_TO_MENU_BTN);
    resumeButton.setTexture (resumeButtonTexture);
    restartButton.setTexture (restartButtonTexture);
    quitButton.setTexture (returnToMenuButtonTexture);

    resumeButton.setPosition (PAUSE_START_X, PAUSE_START_Y);
    restartButton.setPosition (PAUSE_START_X, PAUSE_START_Y + PAUSE_dY);
    quitButton.setPosition (PAUSE_START_X, PAUSE_START_Y + 2 * PAUSE_dY);
    pauseBackground.setFillColor (sf::Color (0, 0, 0, 150)); // Transparent Black

    isPaused = false;
}

void
BattleGround::render (sf::RenderWindow &window)
{
    switch (isPaused)
        {
        case true:
            window.draw (pauseBackground);
            window.draw (resumeButton);
            window.draw (restartButton);
            window.draw (quitButton);
            break;
        case false:
            window.draw (background);
            window.draw (emptyWood);
            window.draw (emptyWoodOther);
            window.draw (treasureChest);
            window.draw (goldText);
            window.draw (scoreText);
            window.draw (gameLogo);
            window.draw (gunnerCard);
            window.draw (cannonShooterCard);
            grid.render (window);
            spawner.render (window);
            for (Bullet *bullet : bullets)
                {
                    bullet->render (window);
                }
            window.draw (pauseButton);
            break;
        }
}

void
BattleGround::updateGoldText ()
{
    goldText.setString (": " + std::to_string (currency.getGold ()));
}

void
BattleGround::updateScoreText ()
{
    scoreText.setString ("Score: " + std::to_string (game->getScore ()));
}

bool
BattleGround::checkCollision (Entity *a, Entity *b)
{
    return a->getBounds ().intersects (b->getBounds ());
}

void
BattleGround::handleInput (sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                {
                    window.close ();
                }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition (window);
                    sf::Vector2f worldPos = window.mapPixelToCoords (pixelPos);

                    if (!isPaused)
                        {
                            if (pauseButton.getGlobalBounds ().contains (worldPos))
                                {
                                    isPaused = true;
                                    std::cout << "[DEBUG] Game Paused!" << std::endl;
                                    return;
                                }
                            if (gunnerCard.getGlobalBounds ().contains (worldPos))
                                {
                                    selectedPirate = GUNNER;
                                    std::cout << "[DEBUG] Gunner Selected!" << std::endl;
                                    return;
                                }
                            else if (cannonShooterCard.getGlobalBounds ().contains (worldPos))
                                {
                                    selectedPirate = CANNON_SHOOTER;
                                    std::cout << "[DEBUG] Cannon Shooter Selected!" << std::endl;
                                    return;
                                }

                            int col = (worldPos.x - CELL_SIZE * GRID_OFFSET_COLS) / CELL_SIZE;
                            int row = (worldPos.y - CELL_SIZE * GRID_OFFSET_ROWS) / CELL_SIZE;

                            if (col >= 0 && col < GRID_COLS - GRID_OFFSET_COLS && row >= 0 && row < GRID_ROWS && selectedPirate != NONE)
                                {
                                    Pirate *newPirate = nullptr;
                                    if (currency.getGold () >= GUNNER_PRICE and selectedPirate == GUNNER)
                                        {
                                            newPirate = new Gunner (IMG_GUNNER_SPRITE, col * CELL_SIZE + GRID_OFFSET_COLS * CELL_SIZE, row * CELL_SIZE + GRID_OFFSET_ROWS * CELL_SIZE);
                                        }
                                    else if (currency.getGold () >= CANNONSHOOTER_PRICE and selectedPirate == CANNON_SHOOTER)
                                        {
                                            newPirate = new CannonShooter (IMG_CANNONSHOOTER_SPRITE, col * CELL_SIZE + GRID_OFFSET_COLS * CELL_SIZE, row * CELL_SIZE + GRID_OFFSET_ROWS * CELL_SIZE);
                                        }

                                    if (newPirate)
                                        {
                                            bool placed = grid.placePirate (col, row, newPirate);
                                            if (placed)
                                                {
                                                    std::cout << "[DEBUG] Pirate Placed at (" << col << ", " << row << ")" << std::endl;
                                                    currency.spendGold (newPirate->getPrice ());
                                                    updateGoldText ();
                                                }
                                            else
                                                {
                                                    std::cout << "[DEBUG] Cell Occupied! Could Not Place Pirate." << std::endl;
                                                    delete newPirate;
                                                }
                                        }
                                    else
                                        {
                                            delete newPirate;
                                        }
                                    selectedPirate = NONE;
                                }
                            else
                                {
                                    std::cout << "[DEBUG] Not Enough Gold!" << std::endl;
                                }
                        }
                    else
                        {
                            if (resumeButton.getGlobalBounds ().contains (worldPos))
                                {
                                    isPaused = false;
                                    std::cout << "[DEBUG] Game Resumed!" << std::endl;
                                }
                            else if (restartButton.getGlobalBounds ().contains (worldPos))
                                {
                                    std::cout << "[DEBUG] Restarting Game!" << std::endl;
                                    game->restartGame (false);
                                }
                            else if (quitButton.getGlobalBounds ().contains (worldPos))
                                {
                                    std::cout << "[DEBUG] Quitting to Menu!" << std::endl;
                                    game->restartGame (true);
                                    return;
                                }
                        }
                }
        }
}

void
BattleGround::update (float deltaTime)
{
    if (isPaused)
        return;

    spawner.update (deltaTime, grid);

    // Check for predator-pirate collision
    for (Predator *enemy : spawner.getEnemies ())
        {
            if (!enemy)
                continue; 

            int col = (enemy->getPosition ().x - CELL_SIZE * GRID_OFFSET_COLS) / CELL_SIZE;
            int row = (enemy->getPosition ().y - CELL_SIZE * GRID_OFFSET_ROWS) / CELL_SIZE;

            if (col >= 0 && col < GRID_COLS && row >= 0 && row < GRID_ROWS)
                {
                    if (col + 1 < GRID_COLS)
                        { 
                            Pirate *pirate = dynamic_cast<Pirate *> (grid.getEntity (col + 1, row));
                            if (pirate)
                                {
                                    std::cout << "[DEBUG] Predator collided with pirate at (" << col + 1 << ", " << row << ")\n";
                                    grid.removeEntity (col + 1, row);
                                    enemy->pauseMovement (); 
                                }
                        }
                }

            if (enemy->getPosition ().x <= (GRID_OFFSET_COLS - 1) * CELL_SIZE + CELL_SIZE * 2 / 3)
                {
                    std::cout << "[DEBUG] Predator reached base! GAME OVER!\n";
                    game->changeState (Game::GAME_OVER);
                    return;
                }
        }

    // Pirate Attacks
    for (int y = 0; y < GRID_ROWS; ++y)
        {
            for (int x = 0; x < GRID_COLS; ++x)
                {
                    Pirate *pirate = dynamic_cast<Pirate *> (grid.getEntity (x, y));
                    if (pirate && grid.get_number_of_enemies_in_row (y) > 0)
                        {
                            Bullet *newBullet = pirate->fireBullet (deltaTime);
                            if (newBullet)
                                {
                                    bullets.push_back (newBullet);
                                    std::cout << "[DEBUG] Bullet added to game. Total bullets: " << bullets.size () << std::endl;
                                }
                        }
                }
        }

    // Bullet-Predator Collision
    for (auto it = bullets.begin (); it != bullets.end ();)
        {
            Bullet *bullet = *it;
            if (!bullet)
                {
                    it = bullets.erase (it);
                    continue;
                }

            bullet->update (deltaTime);
            bool bulletHit = false;

            for (Predator *enemy : spawner.getEnemies ())
                {
                    if (enemy && checkCollision (bullet, enemy))
                        {
                            enemy->takeDamage (bullet->getDamage ());
                            it = bullets.erase (it);
                            delete bullet; 
                            bulletHit = true;
                            break;
                        }
                }

            if (!bulletHit)
                {
                    ++it;
                }
        }

    // Remove Dead Predators
    for (auto it = spawner.getEnemies ().begin (); it != spawner.getEnemies ().end ();)
        {
            Predator *enemy = *it;
            if (!enemy)
                {
                    it = spawner.getEnemies ().erase (it);
                    continue;
                }

            if (enemy->isDefeated ())
                {
                    int row = enemy->getRow ();
                    grid.update_enemy_in_row (row, -1);
                    delete enemy;
                    it = spawner.getEnemies ().erase (it);
                    game->addScore (SCORE_REWARD_AMOUNT);
                    updateScoreText ();
                    currency.addGold (GOLD_REWARD_AMOUNT);
                    updateGoldText ();
                }
            else
                {
                    ++it;
                }
        }
}
