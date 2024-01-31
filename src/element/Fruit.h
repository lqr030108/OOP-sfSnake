#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    // 水果
    struct Fruit
    {
        sf::CircleShape shape_; // 形状
        int score_; // 分数
        // 构造函数
        Fruit(sf::Vector2f position, sf::Color color, int score);
        // 渲染画面
        void render(sf::RenderWindow &window);
    };
}