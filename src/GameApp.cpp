#include "GameApp.hpp"
#include "AppState.hpp"
#include "SurvivalState.hpp"
#include "CampaignState.hpp"
#include "MenuState.hpp"

MenuState GameApp::mState;
SurvivalState GameApp::sState;
CampaignState GameApp::cState;

GameApp::GameApp() : quitFlag(false) {
    // Start in the menu
    state = &mState;
    
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Escape From Arachine", sf::Style::Titlebar | sf::Style::Close);
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
    state = &mState;
}

void GameApp::goSurvival() {
    state = &sState;
}

void GameApp::goCampaign() {
    state = &cState;
}

void GameApp::quit() {
    quitFlag = true;
}

sf::RenderWindow* GameApp::getWindow() {
    return window;
}
