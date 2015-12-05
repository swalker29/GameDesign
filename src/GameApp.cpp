#include "GameApp.hpp"
#include "AppState.hpp"
#include "SurvivalState.hpp"
#include "CampaignState.hpp"
#include "MenuState.hpp"

GameApp::GameApp() : quitFlag(false) {
    mState = std::make_shared<MenuState>();
    sState = std::make_shared<SurvivalState>();
    
    // Start in the menu
    state = mState;
    
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Arachine", sf::Style::Titlebar | sf::Style::Close);
}

GameApp::~GameApp() {
    if (window != nullptr) {
        delete window;
        window = nullptr;
    }
}

void GameApp::run() {
    while (window->isOpen() && !quitFlag) {
        state->handle(*this);
    }
}

void GameApp::goMenu() {
    mState = std::make_shared<MenuState>();
    state = mState;
    run();
}

void GameApp::goSurvival() {
    sState = std::make_shared<SurvivalState>();
    state = sState;
    run();
}

void GameApp::goCampaign() {
    state = cState;
}

void GameApp::quit() {
    quitFlag = true;
}

sf::RenderWindow* GameApp::getWindow() {
    return window;
}
