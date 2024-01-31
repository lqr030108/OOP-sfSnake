#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <iostream>

#include "screen/GameScreen.h"
#include "screen/GameOverScreen.h"

using namespace sfSnake;

// 构造函数
GameScreen::GameScreen()
    : snake_(), grid_()
{
    // 设置得分信息
    score_.setFont(Game::GlobalFont);
    score_.setString(sf::String(L"分数:") + std::to_string(snake_.getScore()));
    score_.setCharacterSize(Game::GlobalVideoMode.width / 25.0f);
    score_.setFillColor(Game::Color::Yellow);
    setOriginMiddle(score_);
    score_.setPosition(
        Game::GlobalVideoMode.width / 2.0f,
        Game::GlobalVideoMode.width * 0.05f);
}
// 处理输入
void GameScreen::handleInput(sf::RenderWindow &window)
{
    snake_.handleInput(window);
    // 获取鼠标信息
    auto mousePosition = sf::Mouse::getPosition(window);
}
// 更新状态
void GameScreen::update(sf::Time delta)
{
    // 开局先设有3堵墙
    while (wall_.size() < 3)
        generateWall();
    // 整个画面总共有5个水果
    while (fruit_.size() < 5)
        generateFruit();
    // 蛇的状态更新
    snake_.update(delta);
    // 是否吃到水果
    snake_.checkFruitCollisions(fruit_);
    // 如果蛇自己撞到自己，游戏结束
    if (snake_.hitSelf() || snake_.checkWallCollisions(wall_))
        Game::MainScreen = std::make_shared<GameOverScreen>(snake_.getScore());
    // 更新得分信息
    score_.setString(sf::String(L"分数:\t") + std::to_string(snake_.getScore()));
}
// 渲染画面
void GameScreen::render(sf::RenderWindow &window)
{
    // 显示网格
    if (Game::GridVisibility)
        grid_.render(window);
    // 显示蛇
    snake_.render(window);
    // 显示水果
    for (auto fruit : fruit_)
        fruit.render(window);
    // 显示得分
    window.draw(score_);
    // 显示墙
    for (auto wall : wall_)
        wall.render(window);
}
// 生成水果
void GameScreen::generateFruit()
{
    // 随机生成水果的位置
    static std::default_random_engine engine(time(NULL));
    // 随机生成水果的颜色
    static std::default_random_engine colorEngine(time(NULL));
    // 产生水果的x轴坐标
    static std::uniform_int_distribution<int> xPos(
        Game::GlobalVideoMode.width / 15.0f,
        Game::GlobalVideoMode.width -
            Game::GlobalVideoMode.width / 10.0f);
    // 产生水果的y轴坐标
    static std::uniform_int_distribution<int> yPos(
        Game::GlobalVideoMode.width / 10.0f,
        Game::GlobalVideoMode.height -
            Game::GlobalVideoMode.width / 15.0f);
    // 水果颜色的取值范围
    static std::uniform_int_distribution<int> fruitColor(0, 7);
    // 水果生成的位置不能在墙里面
    sf::Vector2f fruitPosition;
    do
    {
        fruitPosition = sf::Vector2f(xPos(engine), yPos(engine));
    } while (checkPosition(wall_, fruitPosition));
    // 随机产生不同颜色的水果，黑色和棕色共占25%，红色、蓝色和绿色共占75%
    switch (fruitColor(colorEngine))
    {
    case 0: // black
        fruit_.push_back(Fruit(
            sf::Vector2f(xPos(engine), yPos(engine)),
            Game::Color::Fruit[0],
            0));
        break;
    case 1: // brown
        fruit_.push_back(Fruit(
            fruitPosition,
            Game::Color::Fruit[1],
            0));
        break;
    case 2:
    case 3: // red
        fruit_.push_back(Fruit(
            fruitPosition,
            Game::Color::Fruit[2],
            3));
        break;
    case 4:
    case 5: // blue
        fruit_.push_back(Fruit(
            fruitPosition,
            Game::Color::Fruit[3],
            2));
        break;
    case 6:
    case 7: // green
        fruit_.push_back(Fruit(
            fruitPosition,
            Game::Color::Fruit[4],
            1));
        break;
    default:
        break;
    }
}
// 生成墙
void GameScreen::generateWall()
{
    // 随机生成墙的位置
    static std::default_random_engine engine(time(NULL));
    // 产生墙的x轴坐标
    static std::uniform_int_distribution<int> xPos(
        Game::GlobalVideoMode.width / 15.0f,
        Game::GlobalVideoMode.width -
            Game::GlobalVideoMode.width / 10.0f);
    // 产生墙的y轴坐标
    static std::uniform_int_distribution<int> yPos(
        Game::GlobalVideoMode.width / 10.0f,
        Game::GlobalVideoMode.height -
            Game::GlobalVideoMode.width / 15.0f);
    // wall_.push_back(Wall(sf::Vector2f(xPos(engine), yPos(engine))));

    sf::Vector2f wallPosition;
    bool tooClose = false;
    do
    {
        wallPosition = sf::Vector2f(xPos(engine), yPos(engine));
        tooClose = false;
        for (auto &wall : wall_)
        {
            sf::FloatRect bounds = wall.shape_.getGlobalBounds();
            sf::Vector2f center(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
            if (abs(center.x - wallPosition.x) < Game::GlobalVideoMode.width / 10.0f)
            {
                tooClose = true;
                break;
            }
            if (abs(center.y - wallPosition.y) < Game::GlobalVideoMode.height / 10.0f)
            {
                tooClose = true;
                break;
            }            
            if (wallPosition.x > Game::GlobalVideoMode.width / 3.0f && wallPosition.x < Game::GlobalVideoMode.width / 3.0f * 2.0f)
            {
                tooClose = true;
                break;
            }
            if (wallPosition.y > Game::GlobalVideoMode.height / 3.0f && wallPosition.y < Game::GlobalVideoMode.height / 3.0f * 2.0f)
            {
                tooClose = true;
                break;
            }
        }
    } while (tooClose);
    wall_.push_back(Wall(wallPosition));
}
// 检查水果是不是在墙里面的函数
bool GameScreen::checkPosition(std::deque<Wall> &walls, sf::Vector2f position)
{
    bool in = false;
    for (auto &wall : walls) // 遍历所有的墙
    {
        sf::FloatRect wallRect = wall.shape_.getGlobalBounds();
        sf::FloatRect posRect = sf::FloatRect(position, sf::Vector2f(40.0f, 40.0f));

        if (posRect.intersects(wallRect)) // 检查位置点是否与墙相交
        {
            in = true;
            break; // 如果在墙里，就退出循环
        }
    }
    return in;
}