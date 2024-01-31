#include <SFML/Graphics.hpp>

#include "Wall.h"
#include "Game.h"

using namespace sfSnake;

// 构造函数
Wall::Wall(sf::Vector2f position)
    : shape_(sf::Vector2f(300.0f, 40.0f))
{
    setOriginMiddle(shape_);
    shape_.setPosition(position);
    shape_.setFillColor(Game::Color::Brown);
}
// 渲染画面
void Wall::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}
