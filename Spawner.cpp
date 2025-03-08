#include "Spawner.hpp"
#include <iostream>
#include <cstdlib>

Spawner::Spawner() : spawnRate(7.0f) {  // Start slow, speed up later
    if (!predatorTexture.loadFromFile("assets/predator.png")) {
        std::cerr << "[ERROR] Failed to load predator texture!" << std::endl;
    }
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
        
        if (spawnRate > 1.5f) {
            spawnRate -= 0.2f;  // Make the game progressively harder
            std::cout << "[DEBUG] New spawn rate: " << spawnRate << " seconds" << std::endl;
        }
    }

    for (auto it = enemies.begin(); it != enemies.end();) {
        Predator* enemy = *it;
        enemy->update(deltaTime);
        
        if (enemy->getPosition().x <= 0) {
            delete enemy;
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
}

void Spawner::spawnEnemy() {
    int spawnRow = rand() % 7;
    Predator* newPredator = new Predator("assets/predator.png", 1920, spawnRow * 120 + 120, 100, 1.0f);
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
