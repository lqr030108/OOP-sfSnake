#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    // 选择按钮
    class OptionButton
    {
    private:
        sf::Text text_; // 按钮信息
        sf::Color originColor_; // 颜色

    public:
        // 构造函数
        OptionButton() = default;
        // 析构函数
        ~OptionButton() = default;
        // 样式设置
        void settings(
            sf::String content,
            sf::Font &font,
            float setCharacterSize,
            sf::Color color,
            sf::Vector2f position);
        // 选择设置
        void clear();
        void focused();
        void seleted();
        // 渲染画面
        void render(sf::RenderWindow &window);
        // 判断给定的点是否在OptionButton的文本区域内
        template <typename T>
        bool contains(sf::Vector2<T> point);
    };
    // 判断给定的点是否在OptionButton的文本区域内
    template <typename T>
    bool OptionButton::contains(sf::Vector2<T> point)
    {
        return text_.getGlobalBounds().contains(static_cast<sf::Vector2f>(point));
    }
}