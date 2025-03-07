/// Grid.cpp - Implementation of Grid System
#include "Grid.hpp"
#include "Pirate.hpp"  // Include here in .cpp
#include <iostream>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    cells.resize(rows, std::vector<Entity*>(cols, nullptr));
}

bool Grid::placePirate(int x, int y, Pirate* pirate) {
    if (cells[y][x] == nullptr) {  // Ensure cell is empty
        cells[y][x] = pirate;
        std::cout << "[DEBUG] Pirate added to grid at " << x << ", " << y << std::endl;
        return true;
    }
    std::cout << "[DEBUG] Cell occupied! Cannot place pirate at " << x << ", " << y << std::endl;
    return false;
}

void Grid::update() {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (cells[y][x] != nullptr) {
                cells[y][x]->update(0.1f); // Placeholder update time
            }
        }
    }
}

void Grid::render(sf::RenderWindow &window) {
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (cells[y][x] != nullptr) {
                std::cout << "[DEBUG] Rendering Pirate at " << x << ", " << y << std::endl;
                cells[y][x]->render(window);
            }
        }
    }
}

Entity* Grid::getEntity(int x, int y) { 
  return cells[y][x]; 
}

Pirate* Grid::getPirate(int x, int y) {
    return dynamic_cast<Pirate*>(cells[y][x]);
}
