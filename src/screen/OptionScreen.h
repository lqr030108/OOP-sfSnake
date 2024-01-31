#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "screen/Screen.h"
#include "screen/GameScreen.h"
#include "element/Grid.h"
#include "element/Button.h"
#include "element/OptionButton.h"

namespace sfSnake
{   
    // 选择主题界面
    class OptionScreen : public Screen
    {
    public:
        // 构造函数
        OptionScreen();
        // 三个主要的操作函数
        void handleInput(sf::RenderWindow &window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow &window) override;

    private:
        // 选项
        std::vector<OptionButton> optionName_;
        std::vector<OptionButton> GridShowOptions_;
        std::vector<OptionButton> GridColorOptions_;
        std::vector<OptionButton> BGColorOptions_;
        // 会被修改的主题
        int GridShowfocused_;
        int GridColorfocused_;
        int BGColorfocused_;
        // 网格
        Grid grid_;
        // 选择按钮
        Button returnButton_;
    };
}