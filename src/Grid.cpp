#include "Grid.hpp"
#include "Pirate.hpp"
#include <iostream>

Grid::Grid (int rows, int cols) : rows (rows), cols (cols)
{
    cells.resize (rows, std::vector<Entity *> (cols, nullptr));
    current_available_enemies.resize (rows, 0);
}

bool
Grid::placePirate (int x, int y, Pirate *pirate)
{
    if (cells[y][x] == nullptr)
        {
            cells[y][x] = pirate;
            std::cout << "[DEBUG] Pirate added to grid at " << x << ", " << y << std::endl;
            return true;
        }
    std::cout << "[DEBUG] Cell occupied! Cannot place pirate at " << x << ", " << y << std::endl;
    return false;
}

void
Grid::render (sf::RenderWindow &window)
{
    for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
                {
                    if (cells[y][x] != nullptr)
                        {
                            std::cout << "[DEBUG] Rendering Pirate at " << x << ", " << y << std::endl;
                            cells[y][x]->render (window);
                        }
                }
        }
}

Entity *
Grid::getEntity (int x, int y)
{
    return cells[y][x];
}

void
Grid::removeEntity (int x, int y)
{
    if (cells[y][x] != nullptr)
        {
            delete cells[y][x];
            cells[y][x] = nullptr;
            std::cout << "[DEBUG] Pirate at (" << x << ", " << y << ") removed!\n";
        }
}

int
Grid::get_number_of_enemies_in_row (int current_row)
{
    return current_available_enemies[current_row];
}

void
Grid::update_enemy_in_row (int current_row, int amount)
{
    current_available_enemies[current_row] += amount;
}