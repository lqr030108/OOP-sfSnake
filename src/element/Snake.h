#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <deque>

#include "Fruit.h"
#include "Wall.h"

namespace sfSnake
{
    // 方向向量
    typedef sf::Vector2f Direction;
    // 节点信息向量
    typedef sf::Vector2f SnakePathNode;
    // 蛇
    class Snake
    {
    public:
        // 构造函数
        Snake();
        // 三个主要的操作函数
        void handleInput(sf::RenderWindow &window);
        void update(sf::Time delta);
        void render(sf::RenderWindow &window);
        // 判断是否吃到水果
        void checkFruitCollisions(std::deque<Fruit> &fruits);
        // 判断是否撞到自己
        bool hitSelf() const;
        // 判断是否撞到墙
        bool checkWallCollisions(std::deque<Wall> &walls);
        // 获取得分信息
        unsigned getScore() const;

    private:
        // 初始化蛇的节点
        void initNodes();
        // 根据得分，蛇的长度增加
        void grow(int score);
        // 蛇形移动
        void move();
        // 检查蛇是否出界
        void checkOutOfWindow();
        // 检查自我碰撞的情况
        void checkSelfCollisions();
        bool hitSelf_;
        // 渲染节点
        template <typename T>
        void renderNode(sf::Vector2f &nowPosition, T &shape, sf::RenderWindow &window, int offset);
        SnakePathNode toWindow(SnakePathNode node);

        Direction direction_; // 前进方向
        float nodeRadius_; // 节点半径
        std::deque<SnakePathNode> path_; // 蛇身
        unsigned tailOverlap_; // 蛇尾
        sf::CircleShape nodeShape; // 圆形节点
        sf::RectangleShape nodeMiddle; // 叠加黑色矩形块
        sf::Texture headTexture; // 蛇头
        sf::Sprite headSprite; // 蛇头特效
        static const int InitialSize; // 初始化长度
        unsigned int score_; // 得分
        // 吃到水果的音效
        sf::SoundBuffer pickupBuffer_;
        sf::Sound pickupSound_;
        // 游戏结束的音效
        sf::SoundBuffer dieBuffer_;
        sf::Sound dieSound_;
    };
}