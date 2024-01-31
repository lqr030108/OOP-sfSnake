#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace sfSnake
{
    // 按钮
    class Button
    {
    private:
        sf::Texture texture_; // 按钮信息
        sf::Sprite sprite_; // 按钮特效
        bool focused_; // 是否有鼠标悬浮

    public:
        // 构造函数
        Button();
        // 析构函数
        ~Button() = default;
        // 更新按钮信息
        void update(std::string filename, float scale = 1 / 8.0f);
        // 设置按钮位置
        void setPosition(float x, float y);
        // 按钮是否被鼠标悬浮
        void focused(bool status);
        bool focused() const;
        // 判断给定的点是否在Button内
        template <typename T>
        bool contain(sf::Vector2<T>) const;
        // 渲染画面
        void render(sf::RenderWindow &window) const;
    };
    // 判断给定的点是否在Button内
    template <typename T>
    bool Button::contain(sf::Vector2<T> point) const
    {
        return dis(point, sprite_.getPosition()) < (sprite_.getGlobalBounds().width) / 2.0f;
    }
}