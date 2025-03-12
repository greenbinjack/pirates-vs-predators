#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "Grid.hpp"
#include "Predator.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

class Spawner
{
  public:
    enum TYPES_OF_PREDATOR
    {
        RHINOMAN,
        ALIENMAN,
        SNAKEMAN
    };

  private:
    std::vector<Predator *> enemies;
    float spawnRate;
    sf::Clock spawnClock;

  public:
    Spawner ();
    ~Spawner ();

    void update (float deltaTime, Grid &grid);
    void render (sf::RenderWindow &window);
    void spawnEnemy (Grid &grid);
    std::vector<Predator *> &getEnemies ();
    void clearEnemies ();
};
#endif
