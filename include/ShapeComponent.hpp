#pragma once

#include <SFML/Graphics.hpp>

class ShapeComponent
{
public:
    std::shared_ptr<sf::Shape> shape;

    ShapeComponent(std::shared_ptr<sf::Shape> s) : shape(s) { }
    ~ShapeComponent() {}
};