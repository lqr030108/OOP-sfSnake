#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    // 网格
    class Grid
    {
    private:
        sf::RectangleShape gridVline; // 垂直线
        sf::RectangleShape gridHline; // 水平线
    public:
        // 构造函数
        Grid();
        // 析构函数
        ~Grid() = default;
        // 渲染画面
        void render(sf::RenderWindow &window);
    };
    
}