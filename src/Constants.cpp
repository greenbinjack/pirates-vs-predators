#include "Constants.hpp"

void
loadTexture (sf::Texture &texture, const std::string &filePath)
{
    try
        {
            if (!texture.loadFromFile (filePath))
                {
                    throw std::runtime_error ("Failed to load texture: " + filePath);
                }
        }
    catch (const std::exception &e)
        {
            std::cerr << "[ERROR] " << e.what () << std::endl;
            exit (0);
        }
}

void
loadFont (sf::Font &font, const std::string &filePath)
{
    try
        {
            if (!font.loadFromFile (filePath))
                {
                    throw std::runtime_error ("Failed to load texture: " + filePath);
                }
        }
    catch (const std::exception &e)
        {
            std::cerr << "[ERROR] " << e.what () << std::endl;
            exit (0);
        }
}