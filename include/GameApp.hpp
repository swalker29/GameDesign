#ifndef GAMEAPP_HPP
#define GAMEAPP_HPP

#include <SFML/Graphics.hpp>

class SurvivalState;
class CampaignState;
class MenuState;
class AppState;

class GameApp{
    private:
        static SurvivalState sState;
        static CampaignState cState;
        static MenuState mState;

        int quitFlag;
        AppState* state;
        sf::RenderWindow* window;

    public:
        GameApp(sf::RenderWindow* window);
        void goSurvival();
        void goCampaign();
        void goMenu();

        void run();
        void quit() {this->quitFlag = 1; };
        sf::RenderWindow* getWindow() { return this->window; }
};
#endif
