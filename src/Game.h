#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include <cmath>

#include "screen/Screen.h"
#include "element/TitleSprite.h"

namespace sfSnake
{
    class Game
    {
    public:
        Game();            // 构造函数
        ~Game() = default; // 析构函数
        // 游戏运行
        void run();
        // 全局颜色设置
        class Color
        {
        public:
            static const sf::Color Yellow;
            static const sf::Color Green;
            static const sf::Color Brown;
            static const sf::Color Background[3];
            static const sf::Color Grid[3];
            static const sf::Color NotSeleted;
            static const sf::Color Fruit[5];
        };
        // 游戏窗口信息
        static sf::VideoMode GlobalVideoMode;
        // 用于初始化游戏窗口的函数
        static sf::VideoMode initVideoMode_();
        // 游戏字体
        static sf::Font GlobalFont;
        // 字体特效
        static TitleSprite GlobalTitle;
        // 主页面、临时跳转页面、游戏页面
        static std::shared_ptr<Screen> MainScreen;
        static std::shared_ptr<Screen> TmpScreen;
        static std::shared_ptr<Screen> TmpGameScreen;
        // 网格
        static int GridVisibility;
        static int GridColor;
        static int BackgroundColor;
        // 鼠标锁定可以确保玩家的鼠标操作不会受到意外的干扰
        static bool mouseButtonLocked;
        static sf::Clock mouseButtonClock;
        static sf::Time mouseButtonCDtime;

    private:
        void handleInput();          // 处理输入
        void update(sf::Time delta); // 更新数据
        void render();               // 渲染画面
        // 游戏窗口
        sf::RenderWindow window_;
        // 游戏帧率
        sf::Time TimePerFrame_;
        // 游戏背景音乐
        sf::Music bgMusic_;
    };

    // 将图形对象的原点设置为其中心点，并返回图形对象的边界信息
    template <typename T>
    inline sf::FloatRect setOriginMiddle(T &shape)
    {
        sf::FloatRect shapeBounds = shape.getLocalBounds();
        shape.setOrigin(shapeBounds.left + shapeBounds.width / 2,
                        shapeBounds.top + shapeBounds.height / 2);
        return shapeBounds;
    }

    // 求两个向量在平面上的距离
    template <typename T1, typename T2>
    inline double dis(
        sf::Vector2<T1> node1,
        sf::Vector2<T2> node2) noexcept
    {
        return std::sqrt(
            std::pow(
                (
                    static_cast<double>(node1.x) -
                    static_cast<double>(node2.x)),
                2) +
            std::pow(
                (
                    static_cast<double>(node1.y) -
                    static_cast<double>(node2.y)),
                2));
    }

    // 求向量的长度
    template <typename T>
    inline double length(sf::Vector2<T> node) noexcept
    {
        return std::sqrt(
            std::pow(static_cast<double>(node.x), 2) +
            std::pow(static_cast<double>(node.y), 2));
    }
}