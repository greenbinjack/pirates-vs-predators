#include "Spawner.hpp"
#include "Constants.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

Spawner::Spawner() : spawnRate(INTITIAL_SPAWN_RATE) {  
    loadTexture (predatorTexture, IMG_PREDATOR);
    std::srand(std::time(nullptr));
}

Spawner::~Spawner() {
    for (Predator* enemy : enemies) {
        delete enemy;
    }
}

void Spawner::update(float deltaTime, Grid &grid) {
    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate) {
        spawnClock.restart();
        spawnEnemy(grid);
        
        if (spawnRate > MAX_SPAWN_RATE) {
            spawnRate -= DECREAMENT_RATE; 
            std::cout << "[DEBUG] New spawn rate: " << spawnRate << " seconds" << std::endl;
        }
    }

    for (auto it = enemies.begin(); it != enemies.end(); it++) {
        Predator* enemy = *it;
        enemy->update(deltaTime);
    }
}

void Spawner::spawnEnemy(Grid &grid) {
    int spawnRow = rand() % 7;
    Predator* newPredator = new Predator(IMG_PREDATOR, SPAWN_START_POSITION, spawnRow * CELL_SIZE + dCELL_SIZE, PREDATOR_HEALTH, PREDATOR_SPEED, spawnRow);
    enemies.push_back(newPredator);
    grid.update_enemy_in_row (spawnRow, +1);
}

void Spawner::render(sf::RenderWindow &window) {
    for (Predator* enemy : enemies) {
        enemy->render(window);
    }
}

std::vector<Predator*>& Spawner::getEnemies() {
    return enemies;
}

void Spawner::clearEnemies() {
    for (auto& enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}
