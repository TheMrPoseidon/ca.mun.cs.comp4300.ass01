#include <iostream>
#include <fstream>

#include "game.hpp"

Game::Game(std::string &configFile)
{
    std::fstream fin(configFile, std::ios_base::in);

    while (fin)
    {
        std::string type;
        fin >> type;

        if (type == "Window")
        {
            fin >> m_width >> m_height;

            m_window.create(sf::VideoMode(m_width, m_height), "SFML works!");
        }

        else if (type == "Font")
        {
            std::string fontfile;
            uint16_t r, g, b;
            fin >> fontfile >> m_fontSize >> r >> g >> b;

            m_fontColor = sf::Color(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));

            if (!m_font.loadFromFile(fontfile))
            {
                exit(1);
            }
        }

        else if (type == "Circle")
        {
            std::string name;
            float posX, posY, radius;
            float sX, sY;
            uint16_t r, g, b;
            fin >> name >> posX >> posY >> sX >> sY >> r >> g >> b >> radius;

            sf::Color fColor(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
            auto circle = std::make_shared<sf::CircleShape>(radius);
            circle->setFillColor(fColor);

            Entity e;
            e.cName = std::make_shared<NameComponent>(name, m_font, m_fontSize, m_fontColor);
            e.cShape = std::make_shared<ShapeComponent>(circle);
            e.cTransform = std::make_shared<TransformCompontent>(sf::Vector2f(posX, posY), sf::Vector2f(sX, sY));
            entities.push_back(e);
        }

        else if (type == "Rectangle")
        {
            std::string name;
            float posX, posY, shapeWidth, shapeHeight;
            float sX, sY;
            uint16_t r, g, b;

            fin >> name >> posX >> posY >> sX >> sY >> r >> g >> b >> shapeWidth >> shapeHeight;

            sf::Color fColor(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
            auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeWidth, shapeHeight));
            rect->setFillColor(fColor);
            Entity e;
            e.cName = std::make_shared<NameComponent>(name, m_font, m_fontSize, m_fontColor);
            e.cShape = std::make_shared<ShapeComponent>(rect);
            e.cTransform = std::make_shared<TransformCompontent>(sf::Vector2f(posX, posY), sf::Vector2f(sX, sY));
            entities.push_back(e);
        }
    }
}

Game::~Game()
{
}

void Game::run()
{
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed with code = " << event.key.code << "\n";
            }
        }

        m_window.clear();
        for(auto & e : entities)
        {
            // bounce of corner
            auto boundsShape = e.cShape->shape->getGlobalBounds();
            if (e.cTransform->pos.x <= 0 || e.cTransform->pos.x + boundsShape.width >= m_width)
                e.cTransform->velocity.x *= -1.0f;

            if (e.cTransform->pos.y <= 0 || e.cTransform->pos.y + boundsShape.height >= m_height)
                e.cTransform->velocity.y *= -1.0f;

            // draw shapes
            e.cTransform->pos += e.cTransform->velocity;
            e.cShape->shape->setPosition(e.cTransform->pos);
            m_window.draw(*e.cShape->shape);

            // draw centered labels
            auto boundsLabel = e.cName->label->getLocalBounds();
            auto center = e.cTransform->pos + sf::Vector2f(boundsShape.width/2.0f, boundsShape.height/2.0f) - sf::Vector2f(boundsLabel.width/2.0f, boundsLabel.height/2.0f);
            e.cName->label->setPosition(center);
            m_window.draw(*e.cName->label);
        }
        m_window.display();
    }
}