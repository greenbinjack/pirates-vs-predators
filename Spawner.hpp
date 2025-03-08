#ifndef SPAWNER_HPP
#define SPAWNER_HPP
#include "Predator.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Spawner {
private:
    std::vector<Predator*> enemies;
    float spawnRate;
    sf::Clock spawnClock;
    sf::Texture predatorTexture;
public:
    Spawner();
    ~Spawner();
    
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void spawnEnemy();
    std::vector<Predator*>& getEnemies();
    void clearEnemies();
};
#endif
