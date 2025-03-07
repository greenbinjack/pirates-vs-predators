#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;

public:
    Entity(const std::string &textureFile, float x, float y);
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow &window);

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
    
    // 🔹 Added getter function
    sf::Vector2f getPosition() const { return position; }
    sf::Sprite& getSprite() { return sprite; }  // 🔹 Add this function
};
#endif
