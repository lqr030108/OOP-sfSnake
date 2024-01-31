#include "screen/OptionScreen.h"

#include "Game.h"
#include <iostream>

using namespace sfSnake;

// 构造函数
OptionScreen::OptionScreen()
    : optionName_(3),
      GridShowOptions_(2), GridColorOptions_(3), BGColorOptions_(3),
      GridShowfocused_(-1), GridColorfocused_(-1), BGColorfocused_(-1),
      grid_(), returnButton_()
{
    // 字体大小
    float characterSize = Game::GlobalVideoMode.width / 25.f;
    // 初始化选项信息
    optionName_[0].settings(
        L"网格状态：",
        Game::GlobalFont,
        characterSize,
        Game::Color::Yellow,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f, Game::GlobalVideoMode.height / 4.0f));
    optionName_[1].settings(
        L"网格色：",
        Game::GlobalFont,
        characterSize,
        Game::Color::Yellow,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f, Game::GlobalVideoMode.height / 2.0f));
    optionName_[2].settings(
        L"背景色：",
        Game::GlobalFont,
        characterSize,
        Game::Color::Yellow,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f, Game::GlobalVideoMode.height / 4.0f * 3.0f));
    // 网格是否显示
    GridShowOptions_[0].settings(
        L"关",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 15.0f * 7.0f, Game::GlobalVideoMode.height / 4.0f));
    GridShowOptions_[1].settings(
        L"开",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 15.0f * 11.0f, Game::GlobalVideoMode.height / 4.0f));
    // 选择网格的颜色
    GridColorOptions_[0].settings(
        L"白色",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 2.0f, Game::GlobalVideoMode.height / 2.0f));
    GridColorOptions_[1].settings(
        L"黑色",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 3.0f, Game::GlobalVideoMode.height / 2.0f));
    GridColorOptions_[2].settings(
        L"褐色",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 4.0f, Game::GlobalVideoMode.height / 2.0f));
    // 选择背景颜色
    BGColorOptions_[0].settings(
        L"白色",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 2.0f, Game::GlobalVideoMode.height / 4.0f * 3.0f));
    BGColorOptions_[1].settings(
        L"黑色",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 3.0f, Game::GlobalVideoMode.height / 4.0f * 3.0f));
    BGColorOptions_[2].settings(
        L"褐色",
        Game::GlobalFont,
        characterSize,
        Game::Color::NotSeleted,
        sf::Vector2f(Game::GlobalVideoMode.width / 5.0f * 4.0f, Game::GlobalVideoMode.height / 4.0f * 3.0f));
    // 返回原来页面的按钮
    returnButton_.update("assets/image/returnUI.png", 1 / 16.0f);
    returnButton_.setPosition(Game::GlobalVideoMode.width / 15.0f, Game::GlobalVideoMode.width / 15.0f);
}
// 处理输入
void OptionScreen::handleInput(sf::RenderWindow &window)
{
    auto mousePosition = sf::Mouse::getPosition(window);
    GridShowfocused_ = -1;
    GridColorfocused_ = -1;
    BGColorfocused_ = -1;
    // 不显示网格
    if (GridShowOptions_[0].contains(mousePosition))
    {
        GridShowfocused_ = 0;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::GridVisibility = 0;
            return;
        }
    }
    // 显示网格
    if (GridShowOptions_[1].contains(mousePosition))
    {
        GridShowfocused_ = 1;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::GridVisibility = 1;
            return;
        }
    }
    // 白色网格
    if (GridColorOptions_[0].contains(mousePosition))
    {
        GridColorfocused_ = 0;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::GridColor = 0;
            return;
        }
    }
    // 黑色网格
    if (GridColorOptions_[1].contains(mousePosition))
    {
        GridColorfocused_ = 1;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::GridColor = 1;
            return;
        }
    }
    // 褐色网格
    if (GridColorOptions_[2].contains(mousePosition))
    {
        GridColorfocused_ = 2;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::GridColor = 2;
            return;
        }
    }
    // 白色背景
    if (BGColorOptions_[0].contains(mousePosition))
    {
        BGColorfocused_ = 0;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::BackgroundColor = 0;
            return;
        }
    }
    // 黑色背景
    if (BGColorOptions_[1].contains(mousePosition))
    {
        BGColorfocused_ = 1;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::BackgroundColor = 1;
            return;
        }
    }
    // 褐色背景
    if (BGColorOptions_[2].contains(mousePosition))
    {
        BGColorfocused_ = 2;
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::BackgroundColor = 2;
            return;
        }
    }
    // 点击返回按钮
    returnButton_.focused(false);
    if (returnButton_.contain(mousePosition))
    {
        returnButton_.focused(true);
        if (!Game::mouseButtonLocked && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Game::mouseButtonCDtime = sf::Time::Zero;
            Game::mouseButtonLocked = true;
            Game::MainScreen = Game::TmpScreen; // 返回主页面
            Game::TmpScreen = nullptr;
            return;
        }
    }
}
// 更新状态
void OptionScreen::update(sf::Time delta)
{
    // 初始化，先清空原本的状态
    for (auto &i : GridShowOptions_)
        i.clear();
    for (auto &i : GridColorOptions_)
        i.clear();
    for (auto &i : BGColorOptions_)
        i.clear();
    // 导入选择的信息
    GridShowOptions_[Game::GridVisibility].seleted();
    if (GridShowfocused_ != -1)
        GridShowOptions_[GridShowfocused_].focused();
    GridColorOptions_[Game::GridColor].seleted();
    if (GridColorfocused_ != -1)
        GridColorOptions_[GridColorfocused_].focused();
    BGColorOptions_[Game::BackgroundColor].seleted();
    if (BGColorfocused_ != -1)
        BGColorOptions_[BGColorfocused_].focused();
}
// 渲染画面
void OptionScreen::render(sf::RenderWindow &window)
{
    // 显示网格
    if (Game::GridVisibility)
        grid_.render(window);
    // 显示选择
    for (auto &i : optionName_)
        i.render(window);
    for (auto &i : GridShowOptions_)
        i.render(window);
    for (auto &i : GridColorOptions_)
        i.render(window);
    for (auto &i : BGColorOptions_)
        i.render(window);
    // 显示返回按钮
    returnButton_.render(window);
}