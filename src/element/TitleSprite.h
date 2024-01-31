#pragma once

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    // 主页面中logo的特效
    class TitleSprite
    {
    private:
        sf::Texture titleTexture_;
        sf::Sprite titleSprite_;
        bool rotateDirection_;

    public:
        // 构造函数
        TitleSprite();
        // 析构函数
        ~TitleSprite() = default;
        // 更新状态
        void update(sf::Time delta);
        // 显示logo
        void render(sf::RenderWindow &window);
    };
}
