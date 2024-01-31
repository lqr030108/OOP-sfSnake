#include <iostream>

#include "element/TitleSprite.h"
#include "Game.h"

using namespace sfSnake;

// 构造函数
TitleSprite::TitleSprite()
    : titleTexture_(), titleSprite_(), rotateDirection_(true)
{
    // 设置logo样式
    titleTexture_.loadFromFile("assets/image/logo.png");
    titleTexture_.setSmooth(true);
    titleSprite_.setTexture(titleTexture_);
    sf::FloatRect titleSpriteBounds = setOriginMiddle(titleSprite_);
    titleSprite_.setScale(Game::GlobalVideoMode.width / titleSpriteBounds.width * 0.5f, Game::GlobalVideoMode.width / titleSpriteBounds.width * 0.5f);
    titleSprite_.setPosition(Game::GlobalVideoMode.width / 2, Game::GlobalVideoMode.height / 4);
}
// 更新logo的旋转状态
void TitleSprite::update(sf::Time delta)
{
    if (rotateDirection_)
    {
        titleSprite_.rotate(delta.asSeconds());
        if (titleSprite_.getRotation() >= 10.0f && titleSprite_.getRotation() <= 11.0f)
            rotateDirection_ = false;
    }
    else
    {
        titleSprite_.rotate(-delta.asSeconds());
        if (titleSprite_.getRotation() >= 349.0f && titleSprite_.getRotation() <= 350.0f)
            rotateDirection_ = true;
    }
}
// 显示logo
void TitleSprite::render(sf::RenderWindow &window)
{
    window.draw(titleSprite_);
}