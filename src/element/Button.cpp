#include "element/Button.h"
#include "Game.h"

using namespace sfSnake;

// 构造函数
Button::Button()
    : focused_{false}
{
}
// 更新按钮信息
void Button::update(std::string filename, float scale)
{
    if (!texture_.loadFromFile(filename))
        return;
    texture_.setSmooth(true);
    sprite_.setTexture(texture_);
    sf::FloatRect bounds = setOriginMiddle(sprite_);
    sprite_.setScale(Game::GlobalVideoMode.width / bounds.width * scale, Game::GlobalVideoMode.width / bounds.width * scale);
}
// 设置按钮位置
void Button::setPosition(float x, float y)
{
    sprite_.setPosition(x, y);
}
// 按钮被鼠标悬浮时会变色
void Button::focused(bool status)
{
    focused_ = status;
    if (status)
        sprite_.setColor(sf::Color::Yellow);
    else
        sprite_.setColor(sf::Color::White);
}
// 获取按钮是否被悬浮的信息
bool Button::focused() const
{
    return focused_;
}
// 渲染画面
void Button::render(sf::RenderWindow &window) const
{
    window.draw(sprite_);
}

