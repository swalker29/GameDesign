#ifndef GAMEAPP_HPP
#define GAMEAPP_HPP

#include <memory>

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
        std::shared_ptr<SurvivalState> sState;
        std::shared_ptr<CampaignState> cState;
        std::shared_ptr<MenuState> mState;

        bool quitFlag;
        std::shared_ptr<AppState> state;
        sf::RenderWindow* window;

    
};
#endif
