#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "AppState.hpp"
#include "Game.hpp"
#include "SpriteView.hpp"
#include <SFML/Audio.hpp>


class GameApp;

class MenuState : public AppState {
    public:
        MenuState();
        void handle(GameApp& gameApp);
    private:
        int curSelected;
        int numButtons;
		int displacement; 
		int i;
		int j;
		int timeElapsed;
		Game game;
		
		sf::Clock clock;
		sf::Time tElapsed;
        //graphics
        sf::RenderWindow* window;
        sf::View view;
        sf::Font font;
        sf::Text arachineText;
        sf::Text survivalText;
        sf::Text campaignText;
        sf::Text quitText;
		//music
		sf::SoundBuffer mBuffer;
		sf::Sound menuMusic;
		
		SpriteView tileView;
		
        void init();
        void drawBackground();
		void drawMenu();

        void selectPrevButton();
        void selectNextButton();
        void selectButton(GameApp& app);

};

#endif
