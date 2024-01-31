#pragma once

#include <SFML/Graphics.hpp>
#include <deque>

#include "screen/Screen.h"
#include "element/Snake.h"
#include "element/Fruit.h"
#include "element/Wall.h"
#include "element/Grid.h"
#include "element/Button.h"

namespace sfSnake
{
    // 游戏开始界面
    class GameScreen : public Screen
    {
    public:
        // 构造函数
        GameScreen();
        // 三个主要的操作函数
        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;
        // 生成水果的函数
        void generateFruit();
        // 生成墙的函数
        void generateWall();
        // 检查水果是不是在墙里面的函数
        bool checkPosition(std::deque<Wall> &walls, sf::Vector2f position);

    private:
        Snake snake_; // 蛇
        std::deque<Fruit> fruit_; // 所有的水果
        std::deque<Wall> wall_; // 所有的墙
        Grid grid_; // 网格
        sf::Text score_; // 得分
    };
}