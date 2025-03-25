#ifndef GRID_HPP
#define GRID_HPP

#include "Entity.hpp"
#include "Pirate.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Grid
{
  private:
    int rows, cols;
    std::vector<std::vector<Entity *> > cells;
    std::vector<int> current_available_enemies;

  public:
    Grid (int rows, int cols);

    bool placePirate (int x, int y, Pirate *pirate);
    Entity *getEntity (int x, int y);
    void removeEntity (int x, int y);
    int get_number_of_enemies_in_row (int current_row);
    void update_enemy_in_row (int current_row, int amount);

    void render (sf::RenderWindow &window);
};
#endif
