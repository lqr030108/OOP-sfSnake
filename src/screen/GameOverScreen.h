#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include "element/Button.h"
#include "screen/OptionScreen.h"

namespace sfSnake
{
    // 游戏结束页面
    class GameOverScreen : public Screen
    {
    public:
        // 构造函数
        GameOverScreen(std::size_t score);
        // 三个主要的操作函数
        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        sf::Text text_; // 显示的信息
        std::vector<Button> button_; // 按钮
        unsigned score_; // 最终得分
    };
}