#include "Spawner.hpp"
#include <iostream>
#include <cstdlib>

Spawner::Spawner() : spawnTimer(0), spawnRate(3.0f) {  // Initial spawn rate = 3 seconds
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
    spawnTimer += deltaTime;

    // std::cout << "[DEBUG] : " << spawnTimer << " / " << spawnRate << std::endl;

    if (spawnTimer >= spawnRate) {
        std::cout << "[DEBUG] Time to spawn a new predator!" << std::endl;
        spawnEnemy();
        spawnTimer = 0; // Reset timer

        // 🔹 Increase difficulty over time
        if (spawnRate > 1.0f) {
            spawnRate -= 0.1f;
            std::cout << "[DEBUG] New spawn rate: " << spawnRate << " seconds" << std::endl;
        }
    }

    // Update all enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        Predator* enemy = *it;
        enemy->update(deltaTime);

        if (enemy->getPosition().x <= 0) {  // Remove enemy if it reaches left side
            std::cout << "[DEBUG] Predator reached left side! Removing...\n";
            delete enemy;
            it = enemies.erase(it);
        } else {
            ++it;
        }
    }
}

void Spawner::spawnEnemy() {
    float yPosition = 200 + (rand() % 6) * 120;  // Spawn in random row

    std::cout << "[DEBUG] Spawning Predator at X=1920, Y=" << yPosition << std::endl;

    Predator* newPredator = new Predator("assets/predator.png", 1920, yPosition, 100, 2.0f);
    enemies.push_back(newPredator);

    if (!newPredator) {
        std::cerr << "[ERROR] Failed to spawn predator!" << std::endl;
    } else {
        std::cout << "[DEBUG] Predator successfully added to the enemies list!" << std::endl;
    }
}

void Spawner::render(sf::RenderWindow &window) {
    for (Predator* enemy : enemies) {
        enemy->render(window);
    }
}

std::vector<Predator*>& Spawner::getEnemies() {
    return enemies;
}
