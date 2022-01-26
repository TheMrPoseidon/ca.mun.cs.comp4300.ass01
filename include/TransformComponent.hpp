#pragma once

#include <SFML/Graphics.hpp>

class TransformCompontent
{
public:
    sf::Vector2f pos;
    sf::Vector2f velocity;
    TransformCompontent(sf::Vector2f p, sf::Vector2f v): pos(p), velocity(v) {}
    ~TransformCompontent() {}
};