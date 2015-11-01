#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "AppState.hpp"

class GameApp;

class MenuState : public AppState {
    public:
        MenuState();
        void handle(GameApp& gameApp);
    private:
        int curSelected;
        int numButtons;

        //graphics
        sf::RenderWindow* window;
        sf::View view;
        sf::Font font;
        sf::Text arachineText;
        sf::Text survivalText;
        sf::Text campaignText;
        sf::Text quitText;

        void init();
        void draw();

        void selectPrevButton();
        void selectNextButton();
        void selectButton(GameApp& app);

};

#endif
