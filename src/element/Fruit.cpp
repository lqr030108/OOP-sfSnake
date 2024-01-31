#include <SFML/Graphics.hpp>

#include "Fruit.h"
#include "Game.h"

using namespace sfSnake;

// 构造函数
Fruit::Fruit(sf::Vector2f position, sf::Color color, int score)
    : score_(score)
{
    switch (score)
    {
    case 0:
        shape_.setRadius(Game::GlobalVideoMode.width / 100.0f);
        break;
    case 1:
        shape_.setRadius(Game::GlobalVideoMode.width / 150.0f);
        break;
    case 2:
        shape_.setRadius(Game::GlobalVideoMode.width / 200.0f);
        break;
    case 3:
        shape_.setRadius(Game::GlobalVideoMode.width / 256.0f);
        break;    
    default:
        break;
    }
    setOriginMiddle(shape_);
    shape_.setPosition(position);
    shape_.setFillColor(color);
}
// 渲染画面
void Fruit::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}
