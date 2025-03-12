#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity
{
  protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;

  public:
    Entity (const std::string &textureFile, float x, float y);
    virtual ~Entity () = default;

    sf::FloatRect getBounds () const;
    sf::Vector2f getPosition () const;
    sf::Sprite &getSprite ();

    virtual void render (sf::RenderWindow &window) = 0;
    virtual void update (float deltaTime) = 0;
};

#endif
