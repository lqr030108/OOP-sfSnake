#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "screen/GameScreen.h"
#include "screen/GameOverScreen.h"

using namespace sfSnake;

// 构造函数
GameOverScreen::GameOverScreen(std::size_t score)
    : button_(3), score_(score)
{
    // 设置得分信息
    text_.setFont(Game::GlobalFont);
    text_.setString(sf::String(L"最终分数：") + std::to_string(score));
    text_.setFillColor(Game::Color::Yellow);
    text_.setCharacterSize(Game::GlobalVideoMode.width / 15);
    setOriginMiddle(text_);
    text_.setPosition(Game::GlobalVideoMode.width / 2.0f, Game::GlobalVideoMode.height / 4.0f);
    // 设置按钮的图片
    button_[0].update("assets/image/optionUI.png"); // 选择主题
    button_[1].update("assets/image/restartUI.png"); // 重新开始
    button_[2].update("assets/image/exitUI.png"); // 退出游戏
    // 设置按钮的位置
    button_[0].setPosition(Game::GlobalVideoMode.width / 3.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[1].setPosition(Game::GlobalVideoMode.width / 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);
    button_[2].setPosition(Game::GlobalVideoMode.width / 3.0 * 2.0, Game::GlobalVideoMode.height / 5.0 * 3.0);

}
// 处理输入
void GameOverScreen::handleInput(sf::RenderWindow &window)
{
    // 获取鼠标信息
    static sf::Vector2i mousePosition;
    mousePosition = sf::Mouse::getPosition(window);
    // 初始化所有按钮都没有被鼠标选中
    for (auto &i : button_)
        i.focused(false);
    // 点击选择主题按钮
    if (button_[0].contain(mousePosition))
    {
        button_[0].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::TmpScreen = Game::MainScreen;
            Game::MainScreen = std::make_shared<OptionScreen>();
            return;
        }
    }
    // 选择重新开始按钮
    if (button_[1].contain(mousePosition))
    {
        button_[1].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = Game::mouseButtonClock.restart();
            Game::mouseButtonLocked = true;
            Game::MainScreen = std::make_shared<GameScreen>();
            return;
        }
    }
    // 选择退出游戏按钮
    if (button_[2].contain(mousePosition))
    {
        button_[2].focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            window.close();
            return;
        }
    }

}
// 更新状态
void GameOverScreen::update(sf::Time delta)
{
}
// 渲染画面
void GameOverScreen::render(sf::RenderWindow &window)
{
    // 显示得分信息
    window.draw(text_);
    // 显示按钮
    for (auto &button : button_)
        button.render(window);
}