#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <string>

#include "screen/MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

// 定义颜色
const sf::Color Game::Color::Yellow =
    sf::Color(0xFFD700ff);
const sf::Color Game::Color::Green =
    sf::Color(0x008000ff);
const sf::Color Game::Color::Brown =
    sf::Color(0x8B4513ff);
const sf::Color Game::Color::Background[] =
    {
        sf::Color(0xF0F8FF55), // White
        sf::Color(0x40405055), // Black
        sf::Color(0xD2B48C55)  // Brown
};
const sf::Color Game::Color::Grid[] =
    {
        sf::Color(0xF0F8FF55), // White
        sf::Color(0x40405055), // Black
        sf::Color(0xD2B48C55)  // Brown
};
const sf::Color Game::Color::NotSeleted =
    sf::Color(0x00000055);
const sf::Color Game::Color::Fruit[] =
    {
        sf::Color(0x000000ff), // Black
        sf::Color(0xCD853Fff), // Brown
        sf::Color(0xFF0000ff), // Red
        sf::Color(0x0000FFff), // Blue
        sf::Color(0x008000ff)  // Green
};

// 初始化游戏窗口
sf::VideoMode Game::initVideoMode_()
{
    // 将游戏窗口大小设为桌面大小的一半
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    return sf::VideoMode(
        desktopMode.width / 2.0f,
        desktopMode.height / 2.0f,
        desktopMode.bitsPerPixel);
}
// 初始化存储游戏窗口信息的静态成员变量 GlobalVideoMode
sf::VideoMode Game::GlobalVideoMode = Game::initVideoMode_();

// 游戏字体和特效
sf::Font Game::GlobalFont = sf::Font();
TitleSprite Game::GlobalTitle = TitleSprite();

// 初始化智能指针，指向界面对象
std::shared_ptr<Screen> Game::MainScreen = std::make_shared<MenuScreen>();
std::shared_ptr<Screen> Game::TmpScreen = nullptr;
std::shared_ptr<Screen> Game::TmpGameScreen = nullptr;

// 初始化网格
int Game::GridVisibility = 0;
int Game::GridColor = 0;
int Game::BackgroundColor = 0;


// 初始化鼠标锁定
sf::Clock Game::mouseButtonClock = sf::Clock();
sf::Time Game::mouseButtonCDtime = sf::Time();
bool Game::mouseButtonLocked = false;

// 构造函数
Game::Game()
    : TimePerFrame_(sf::seconds(1.f / 100.f))
{
    // 设置窗口信息
    window_.create(
        GlobalVideoMode,   // videoMode
        "GreedySnake",      // window name
        sf::Style::Close); // window Style
    // 设置游戏的图标
    sf::Image icon;
    icon.loadFromFile("assets/image/icon.png");
    window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // 设置背景音乐
    bgMusic_.openFromFile("assets/music/bg_music.wav");
    bgMusic_.setVolume(30);
    bgMusic_.setLoop(true);
    bgMusic_.play();
}
// 处理输入
void Game::handleInput()
{
    // 检查是否有新的事件（关闭窗口）发生
    static sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
    // 处理键盘或鼠标输入
    Game::MainScreen->handleInput(window_);
}
// 更新数据
void Game::update(sf::Time delta)
{
    Game::MainScreen->update(delta);
}
// 渲染画面
void Game::render()
{
    window_.clear(Color::Background[BackgroundColor]);
    Game::MainScreen->render(window_);
    window_.display();
}
// 游戏运行
void Game::run()
{
    // 用于计算从上次循环到当前时刻经过的时间
    sf::Clock clock;
    // 用于记录从上次循环到当前时刻经过的时间总和
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mouseButtonClock.restart();
    // 游戏运行后，窗口打开，进入游戏
    while (window_.isOpen())
    {
        // 调用 clock.restart() 函数获取从上次循环到当前时刻经过的时间，并将计时器重置为当前时刻
        sf::Time delta = clock.restart();
        // 将 delta 加到 timeSinceLastUpdate 中，表示从上次循环到当前时刻经过的时间总和增加了 delta
        timeSinceLastUpdate += delta;
        // 只要 timeSinceLastUpdate 大于 TimePerFrame_，就表示已经经过了足够的时间，可以进行一次游戏循环
        while (timeSinceLastUpdate > TimePerFrame_)
        {
            timeSinceLastUpdate -= TimePerFrame_;
            // 处理输入
            handleInput();
            // 更新状态
            update(TimePerFrame_);
            // 渲染画面
            render();
        }
        // 鼠标锁定
        delta = mouseButtonClock.restart();
        mouseButtonCDtime += delta;
        if (mouseButtonCDtime.asSeconds() > 0.5f)
        {
            mouseButtonCDtime -= sf::seconds(0.5f);
            mouseButtonLocked = false;
        }
    }
}