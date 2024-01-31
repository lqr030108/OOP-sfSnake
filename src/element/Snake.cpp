#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "element/Snake.h"
#include "Game.h"
#include "element/Fruit.h"
#include "element/Wall.h"

#include "screen/GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

// 构造函数
Snake::Snake()
    : hitSelf_(false),
      direction_(Direction(0, -1)),
      nodeRadius_(Game::GlobalVideoMode.width / 100.0f),
      tailOverlap_(0u),
      nodeShape(nodeRadius_),
      nodeMiddle(sf::Vector2f(nodeRadius_ * std::sqrt(3), nodeRadius_)),
      score_(InitialSize)
{
    // 初始化节点
    initNodes();
    // 黄色圆形
    nodeShape.setFillColor(sf::Color(0xf1c40fff));
    // 黑色矩形块
    nodeMiddle.setFillColor(sf::Color(0x1c2833ff));
    // 设置节点的原点是中心点
    setOriginMiddle(nodeShape);
    setOriginMiddle(nodeMiddle);
    // 设置蛇头
    headTexture.loadFromFile("assets/image/snakeHeadImage.png");
    headTexture.setSmooth(true);
    sf::Vector2u TextureSize = headTexture.getSize();
    float headScale = nodeRadius_ / TextureSize.y * 2.6;
    headSprite.setTexture(headTexture);
    headSprite.setScale(headScale, headScale);
    setOriginMiddle(headSprite);
    // 设置吃到水果的音效
    pickupBuffer_.loadFromFile("assets/sounds/pickup.wav");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);
    // 设置游戏结束的音效
    dieBuffer_.loadFromFile("assets/sounds/die.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}
// 初始化节点
void Snake::initNodes()
{
    path_.push_back(SnakePathNode(
        Game::GlobalVideoMode.width / 2.0f,
        Game::GlobalVideoMode.height / 2.0f));
    for (int i = 1; i <= 10 * InitialSize; i++)
    {
        path_.push_back(SnakePathNode(
            Game::GlobalVideoMode.width / 2.0f -
                direction_.x * i * nodeRadius_ / 5.0,
            Game::GlobalVideoMode.height / 2.0f -
                direction_.y * i * nodeRadius_ / 5.0));
    }
}
// 处理输入
void Snake::handleInput(sf::RenderWindow &window)
{
    // 键盘控制上下左右
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction_ = Direction(0, -1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction_ = Direction(0, 1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        direction_ = Direction(-1, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction_ = Direction(1, 0);
    // 鼠标点击控制前进方向
    static double directionSize;
    if (!Game::mouseButtonLocked)
    {
        if (
            sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
            sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            static sf::Vector2i MousePosition;
            MousePosition = sf::Mouse::getPosition(window);
            if (
                dis(MousePosition,
                    sf::Vector2f(
                        Game::GlobalVideoMode.width / 15.0f * 14.0f,
                        Game::GlobalVideoMode.width / 15.0f)) >
                Game::GlobalVideoMode.width / 16.0f)
            {
                direction_ =
                    static_cast<sf::Vector2f>(MousePosition) -
                    toWindow(path_.front());
                directionSize = length(direction_);
                direction_.x /= directionSize;
                direction_.y /= directionSize;
            }
        }
    }
}
// 更新状态
void Snake::update(sf::Time delta)
{
    move();
    static int count = 0;
    if (++count >= 40)
    {
        checkOutOfWindow();
        count -= 40;
    }
    checkSelfCollisions();
}
// 检查是否吃到水果
void Snake::checkFruitCollisions(std::deque<Fruit> &fruits)
{
    auto toRemove = fruits.end();
    SnakePathNode headnode = path_.front();

    for (auto i = fruits.begin(); i != fruits.end(); ++i)
    {
        if (dis(i->shape_.getPosition(), toWindow(headnode)) < nodeRadius_ + i->shape_.getRadius())
            toRemove = i;
    }
    // 吃到水果后，发出音效，蛇变长，水果减少
    if (toRemove != fruits.end())
    {
        pickupSound_.play();
        grow(toRemove->score_);
        fruits.erase(toRemove);
    }
}
// 蛇增长
void Snake::grow(int score)
{
    tailOverlap_ += score * 10;
    score_ += score;
}
// 获取得分信息
unsigned Snake::getScore() const
{
    return score_ - 5;
}
// 获取是否撞到自己的信息
bool Snake::hitSelf() const
{
    return hitSelf_;
}
// 移动
void Snake::move()
{
    SnakePathNode &headNode = path_.front();

    path_.push_front(SnakePathNode(
        headNode.x + direction_.x * nodeRadius_ / 5.0,
        headNode.y + direction_.y * nodeRadius_ / 5.0));
    if (tailOverlap_)
        tailOverlap_--;
    else
        path_.pop_back();
}
// 检查自己有没有撞到自己
void Snake::checkSelfCollisions()
{
    SnakePathNode head = toWindow(path_.front());
    int count = 0;

    for (auto i = path_.begin(); i != path_.end(); i++, count++)
        if (count >= 50 && dis(head, toWindow(*i)) < 2.0f * nodeRadius_)
        {
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitSelf_ = true;
            break;
        }
}
// 检查有没有撞到墙
bool Snake::checkWallCollisions(std::deque<Wall> &walls)
{
    SnakePathNode headnode = path_.front();
    bool hitWall_ = false;
    for (auto& wall : walls) // 遍历所有的墙
    {
        sf::FloatRect wallRect = wall.shape_.getGlobalBounds();
        sf::FloatRect headRect = sf::FloatRect(toWindow(headnode), sf::Vector2f(nodeRadius_, nodeRadius_));
        if (headRect.intersects(wallRect)) // 检查蛇头是否与墙相交
        {
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitWall_ = true;
            break; // 如果撞到了墙，就退出循环
        }
    }
    return hitWall_;
}
// 检查是否出界
void Snake::checkOutOfWindow()
{
    auto inWindow = [](SnakePathNode &node) -> bool
    {
        return node.x >= 0 &&
               node.x <= Game::GlobalVideoMode.width &&
               node.y >= 0 &&
               node.y <= Game::GlobalVideoMode.height;
    };
    bool OutOfWindow = true;
    for (auto i : path_)
    {
        if (inWindow(i))
            OutOfWindow = false;
    }
    if (OutOfWindow)
    {
        SnakePathNode &tail = path_.back();
        if (tail.x < 0)
            for (auto &i : path_)
                i.x = i.x + Game::GlobalVideoMode.width;
        else if (tail.x > Game::GlobalVideoMode.width)
            for (auto &i : path_)
                i.x = i.x - Game::GlobalVideoMode.width;
        else if (tail.y < 0)
            for (auto &i : path_)
                i.y = i.y + Game::GlobalVideoMode.height;
        else if (tail.y > Game::GlobalVideoMode.height)
            for (auto &i : path_)
                i.y = i.y - Game::GlobalVideoMode.height;
    }
}
// 让蛇从另一边回到屏幕上
SnakePathNode Snake::toWindow(SnakePathNode node)
{
    while (node.x < 0)
        node.x = node.x + Game::GlobalVideoMode.width;
    while (node.x > Game::GlobalVideoMode.width)
        node.x = node.x - Game::GlobalVideoMode.width;
    while (node.y < 0)
        node.y = node.y + Game::GlobalVideoMode.height;
    while (node.y > Game::GlobalVideoMode.height)
        node.y = node.y - Game::GlobalVideoMode.height;
    return node;
}
// 渲染画面
void Snake::render(sf::RenderWindow &window)
{
    static int count;
    static SnakePathNode lastSnakeNode, lastMiddleNode, nowSnakeNode;
    static float angle;
    static sf::Vector2f recDirection;
    static SnakePathNode wNowHeadNode;

    lastSnakeNode = *path_.begin();
    wNowHeadNode = toWindow(lastSnakeNode);
    headSprite.setPosition(wNowHeadNode);
    recDirection = direction_;
    angle =
        std::acos(recDirection.y / length(recDirection)) /
        3.14159265358979323846 * 180.0;
    if (direction_.x > 0)
        angle = -angle;
    headSprite.setRotation(angle);

    renderNode(wNowHeadNode, headSprite, window, 3);

    count = 1;
    for (auto i = path_.begin() + 1; i != path_.end(); i++, count++)
    {
        if (count % 5 == 0)
        {
            if (count % 2)
                lastMiddleNode = *i;
            else
            {
                nowSnakeNode = *i;

                recDirection = nowSnakeNode - lastSnakeNode;
                angle =
                    std::acos(recDirection.y / length(recDirection)) /
                    3.14159265358979323846 * 180.0;
                if (recDirection.x > 0)
                    angle = -angle;
                nodeMiddle.setRotation(angle);

                static SnakePathNode wNowSnakeNode;
                static SnakePathNode wMiddleNode;
                wNowSnakeNode = toWindow(nowSnakeNode);
                wMiddleNode = toWindow(lastMiddleNode);
                renderNode(wNowSnakeNode, nodeShape, window, 0);
                renderNode(wMiddleNode, nodeMiddle, window, 0);

                lastSnakeNode = nowSnakeNode;
            }
        }
    }
}
// 渲染节点
template <typename T>
void Snake::renderNode(sf::Vector2f &nowPosition, T &shape, sf::RenderWindow &window, int offset)
{
    shape.setPosition(nowPosition);
    window.draw(shape);

    if (nowPosition.x <= nodeRadius_ + offset)
    {
        shape.setPosition(nowPosition + sf::Vector2f(Game::GlobalVideoMode.width, 0));
        window.draw(shape);
    }
    else if (nowPosition.x >= Game::GlobalVideoMode.width - nodeRadius_ - offset)
    {
        shape.setPosition(nowPosition - sf::Vector2f(Game::GlobalVideoMode.width, 0));
        window.draw(shape);
    }

    if (nowPosition.y <= nodeRadius_ + offset)
    {
        shape.setPosition(nowPosition + sf::Vector2f(0, Game::GlobalVideoMode.height));
        window.draw(shape);
    }
    else if (nowPosition.y >= Game::GlobalVideoMode.height - nodeRadius_ - offset)
    {
        shape.setPosition(nowPosition - sf::Vector2f(0, Game::GlobalVideoMode.height));
        window.draw(shape);
    }

    if (nowPosition.x <= nodeRadius_ + offset && nowPosition.y <= nodeRadius_ + offset)
    {
        shape.setPosition(nowPosition + sf::Vector2f(Game::GlobalVideoMode.width, Game::GlobalVideoMode.height));
        window.draw(shape);
    }
    else if (nowPosition.x >= Game::GlobalVideoMode.width - nodeRadius_ - offset && nowPosition.y >= Game::GlobalVideoMode.height - nodeRadius_ - offset)
    {
        shape.setPosition(nowPosition - sf::Vector2f(Game::GlobalVideoMode.width, Game::GlobalVideoMode.height));
        window.draw(shape);
    }
}