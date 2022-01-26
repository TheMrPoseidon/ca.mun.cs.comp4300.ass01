#pragma once

#include "ShapeComponent.hpp"
#include "NameComponent.hpp"
#include "TransformComponent.hpp"

class Entity
{
public:
    std::shared_ptr<ShapeComponent> cShape = nullptr;
    std::shared_ptr<NameComponent> cName = nullptr;
    std::shared_ptr<TransformCompontent> cTransform = nullptr;
    Entity(/* args */);
    ~Entity();
};