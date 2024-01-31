#include "element/OptionButton.h"

#include "Game.h"
#include <iostream>

using namespace sfSnake;

// 设置样式
void OptionButton::settings(
    sf::String content,
    sf::Font &font,
    float characterSize,
    sf::Color color,
    sf::Vector2f position)
{
    text_.setFont(font);
    text_.setString(content);
    text_.setCharacterSize(characterSize);
    text_.setFillColor(color);
    setOriginMiddle(text_);
    text_.setPosition(position);
    originColor_ = color;
}
// 重置样式
void OptionButton::clear()
{
    text_.setStyle(sf::Text::Regular);
    text_.setFillColor(originColor_);
}
// 悬浮样式
void OptionButton::focused()
{
    text_.setStyle(sf::Text::Underlined);
}
// 选中样式
void OptionButton::seleted()
{
    text_.setFillColor(Game::Color::Yellow);
}
// 渲染画面
void OptionButton::render(sf::RenderWindow &window)
{
    window.draw(text_);
}