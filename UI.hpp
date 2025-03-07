/// UI.hpp - Handles HUD & Buttons
#ifndef UI_HPP
#define UI_HPP
#include <SFML/Graphics.hpp>
#include "Currency.hpp"

class UI {
private:
    sf::Font font;
    sf::Text goldText;
public:
    UI();
    void update(int gold);
    void render(sf::RenderWindow &window);
};
#endif
