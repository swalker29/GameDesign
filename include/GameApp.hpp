#ifndef GAMEAPP_HPP
#define GAMEAPP_HPP

#include <SFML/Graphics.hpp>

class SurvivalState;
class CampaignState;
class MenuState;
class AppState;

class GameApp{
    public:
        GameApp();
        
        ~GameApp();
        
        void goSurvival();
        void goCampaign();
        void goMenu();

        void run();
        void quit();
        
        sf::RenderWindow* getWindow();
    
    private:
        static SurvivalState sState;
        static CampaignState cState;
        static MenuState mState;

        bool quitFlag;
        AppState* state;
        sf::RenderWindow* window;

    
};
#endif
