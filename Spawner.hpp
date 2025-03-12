#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "Predator.hpp"
#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

class Spawner {
private:
    std::vector<Predator*> enemies;
    float spawnRate;
    sf::Clock spawnClock;
    sf::Texture predatorTexture;
public:
    Spawner();
    ~Spawner();
    
    void update(float deltaTime, Grid &grid);
    void render(sf::RenderWindow &window);
    void spawnEnemy(Grid &grid);
    std::vector<Predator*>& getEnemies();
    void clearEnemies();
};
#endif
