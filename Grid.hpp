#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.hpp"
#include "Pirate.hpp"

class Grid {
private:
    int rows, cols;
    std::vector<std::vector<Entity*>> cells;
public:
    Grid(int rows, int cols);

    bool placePirate(int x, int y, Pirate* pirate);
    Entity* getEntity(int x, int y);
    void removeEntity (int x, int y);  
    
    void render(sf::RenderWindow &window);
};
#endif
