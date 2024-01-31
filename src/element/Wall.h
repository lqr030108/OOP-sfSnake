#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    // 墙
    struct Wall
    {
        sf::RectangleShape shape_; // 形状
        // 构造函数
        Wall(sf::Vector2f position);
        // 渲染画面
        void render(sf::RenderWindow &window);
    };
}