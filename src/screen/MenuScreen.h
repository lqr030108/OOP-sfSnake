#pragma once

#include <SFML/Graphics.hpp>

#include "screen/Screen.h"
#include "element/Button.h"
#include "element/OptionButton.h"

#include <vector>

namespace sfSnake
{
    // 主页面
    class MenuScreen : public Screen
    {
    public:
        // 构造函数
        MenuScreen();
        // 重写三个主要的操作函数
        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        // 主页面的按钮
        std::vector<Button> button_;
    };
}