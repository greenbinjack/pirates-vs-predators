#include "Spawner.hpp"
#include "Constants.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Spawner::Spawner() : spawnRate(INTITIAL_SPAWN_RATE) {  
    try {
        if (!predatorTexture.loadFromFile("assets/predator.png")) {
            throw std::runtime_error("Failed to load predator texture!");
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
    std::srand(std::time(nullptr));
}

Spawner::~Spawner() {
    for (Predator* enemy : enemies) {
        delete enemy;
    }
}

void Spawner::update(float deltaTime) {
    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate) {
        spawnClock.restart();
        spawnEnemy();
        
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

void Spawner::spawnEnemy() {
    int spawnRow = rand() % 7;
    Predator* newPredator = new Predator("assets/predator.png", SPAWN_START_POSITION, spawnRow * CELL_SIZE + dCELL_SIZE, PREDATOR_HEALTH, PREDATOR_SPEED);
    enemies.push_back(newPredator);
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
