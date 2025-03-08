#include "Spawner.hpp"
#include <iostream>
#include <cstdlib>

Spawner::Spawner() : spawnTimer(0), spawnRate(3.0f) {  // Initial spawn rate = 3 seconds
    if (!predatorTexture.loadFromFile("assets/predator.png")) {
        std::cerr << "[ERROR] Failed to load predator texture!" << std::endl;
    }
}

Spawner::~Spawner() {
    // Clean up all enemies
    for (Predator* enemy : enemies) {
        delete enemy;
    }
}

void Spawner::update(float deltaTime) {
    spawnTimer += deltaTime;

    if (spawnTimer >= spawnRate) {
        std::cout << "[DEBUG] Time to spawn a new predator!" << std::endl;
        spawnEnemy();
        spawnTimer = 0; // Reset timer

        // 🔹 Increase difficulty over time by decreasing spawn rate
        if (spawnRate > 1.0f) {
            spawnRate -= 0.1f;
            std::cout << "[DEBUG] New spawn rate: " << spawnRate << " seconds" << std::endl;
        }
    }

    // Update all enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        Predator* enemy = *it;
        enemy->update(deltaTime);

        // If predator reaches the left side (column 10), remove it
        if (enemy->getPosition().x <= 0) {
            std::cout << "[DEBUG] Predator reached left side! Removing...\n";
            delete enemy;
            it = enemies.erase(it);  // Remove the defeated predator
        } else {
            ++it;
        }
    }
}

void Spawner::spawnEnemy() {
    // Predators spawn at columns 12 and 13 (index 11 and 12)
    int spawnRow = rand() % 7;  // Random row between 0 and 6 (7 rows)
    
    // Predator is spawned at the end of the screen, at columns 12 and 13
    float xPosition = 1920;  // Right side of the screen (spawn position for columns 12 and 13)
    float yPosition = 120 + spawnRow * 120;  // Random vertical position for spawning the predator

    std::cout << "[DEBUG] Spawning Predator at X=" << xPosition << ", Y=" << yPosition << std::endl;

    // Create a new predator at the position
    Predator* newPredator = new Predator("assets/predator.png", xPosition, yPosition, 100, 2.0f);

    // Add the newly created predator to the enemies vector
    enemies.push_back(newPredator);

    if (!newPredator) {
        std::cerr << "[ERROR] Failed to spawn predator!" << std::endl;
    } else {
        std::cout << "[DEBUG] Predator successfully added to the enemies list!" << std::endl;
    }
}

void Spawner::render(sf::RenderWindow &window) {
    // Render each enemy predator
    for (Predator* enemy : enemies) {
        enemy->render(window);
    }
}

std::vector<Predator*>& Spawner::getEnemies() {
    // Return reference to the enemies vector
    return enemies;
}

void Spawner::clearEnemies() {
    // Delete all enemies and clear the enemies list
    for (auto& enemy : enemies) {
        delete enemy;
    }
    enemies.clear();  // Remove all enemies
}
