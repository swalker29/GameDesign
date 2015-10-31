#include "GameApp.hpp"
#include "AppState.hpp"
#include "SurvivalState.hpp"
#include "CampaignState.hpp"
#include "MenuState.hpp"

MenuState GameApp::mState;
SurvivalState GameApp::sState;
CampaignState GameApp::cState;

GameApp::GameApp(sf::RenderWindow* window) :
    window(window)
   // quitFlag(0)
{
    //sets the default state we start in
    this->state = &sState;
}

void GameApp::run() {
    //while (!quitFlag) {
        this->state->handle(*this);
    //}
}

void GameApp::goMenu() {
    this->state = &mState;
}

void GameApp::goSurvival() {
    this->state = &sState;
}

void GameApp::goCampaign(){
    this->state = &cState;
}
