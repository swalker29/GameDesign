#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "AppState.hpp"
#include <SFML/Audio.hpp>

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
		//music
		//sf::SoundBuffer mBuffer;
		sf::Music menuMusic;
		
        void init();
        void draw();

        void selectPrevButton();
        void selectNextButton();
        void selectButton(GameApp& app);

};

#endif
