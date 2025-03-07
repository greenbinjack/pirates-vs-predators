#ifndef SPAWNER_HPP
#define SPAWNER_HPP
#include "Predator.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Spawner {
private:
    std::vector<Predator*> enemies;
    float spawnTimer;
    float spawnRate;  // Time between spawns
    sf::Texture predatorTexture;  // Store texture for efficiency

public:
    Spawner();
    ~Spawner();
    
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void spawnEnemy();  // Function to spawn new enemies
    std::vector<Predator*>& getEnemies();  // Allows access to enemies
};
#endif
