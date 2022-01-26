#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Game
{
private:
    sf::RenderWindow m_window;
    sf::Font m_font;
    std::vector<Entity> entities;

    uint16_t m_width, m_height;
    uint16_t m_fontSize;
    sf::Color m_fontColor;

public:
    Game(std::string & configFile);
    ~Game();
    void run();
};
