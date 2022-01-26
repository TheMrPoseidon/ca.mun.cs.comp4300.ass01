#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class NameComponent
{
private:
    
public:
    std::shared_ptr<std::string> name = nullptr;
    std::shared_ptr<sf::Text> label = nullptr;
    NameComponent(std::string n, sf::Font & font, uint8_t fontSize, sf::Color & fontColor) {
        name = std::make_shared<std::string>(n);
        label = std::make_shared<sf::Text>(n, font, fontSize);
        label->setFillColor(fontColor);
    };
    ~NameComponent(){}
};
