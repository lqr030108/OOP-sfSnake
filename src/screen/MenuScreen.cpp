#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "Game.h"
#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"
#include "screen/OptionScreen.h"

using namespace sfSnake;
// 构造函数
MenuScreen::MenuScreen()
    : button_(3)
{
    // 字体设置
    Game::GlobalFont.loadFromFile("assets/fonts/PF.ttf");
    // 三个按钮的图片设置
    button_[0].update("assets/image/optionUI.png"); // 选择主题
    button_[1].update("assets/image/startUI.png"); // 开始游戏
    button_[2].update("assets/image/exitUI.png"); // 退出游戏
    // 三个按钮的位置设置
    button_[0].setPosition(Game::GlobalVideoMode.width / 3.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[1].setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[2].setPosition(Game::GlobalVideoMode.width / 3.0 * 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
}
// 处理输入
void MenuScreen::handleInput(sf::RenderWindow &window)
{
    // 获取鼠标点击的信息
    static sf::Vector2i mousePosition;
    mousePosition = sf::Mouse::getPosition(window);
    // 初始化所有按钮都是没被鼠标悬浮的状态
    for (auto &i : button_)
        i.focused(false);
    // 点击选择主题按钮
    if (button_[0].contain(mousePosition))
    {
        // 按钮上有鼠标悬浮，变色
        button_[0].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen = Game::MainScreen; // 主页面被设为临时页面，用于之后的返回
            Game::MainScreen = std::make_shared<OptionScreen>(); // 进入选择主题页面
            return;
        }
    }
    // 点击开始游戏按钮
    if (button_[1].contain(mousePosition))
    {
        // 按钮上有鼠标悬浮，变色
        button_[1].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonLocked = true;
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::MainScreen = std::make_shared<GameScreen>(); // 进入游戏开始页面
            return;
        }
    }
    // 点击退出游戏按钮
    if (button_[2].contain(mousePosition))
    {
        // 按钮上有鼠标悬浮，变色
        button_[2].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            window.close();
            return;
        }
    }
}
// 更新状态
void MenuScreen::update(sf::Time delta)
{
    Game::GlobalTitle.update(delta);
}
// 渲染画面
void MenuScreen::render(sf::RenderWindow &window)
{
    Game::GlobalTitle.render(window);
    for (auto &button : button_)
        button.render(window);
}