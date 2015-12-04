#include "MenuState.hpp"
#include "GameApp.hpp"


static const std::string FONT_FILENAME = "assets/DroidSans.ttf";
static const std::string MUSIC_FILENAME = "assets/menuMusic.wav";
static const std::string LEVEL_TILE_SHEET_FILENAME = "assets/tileset.png";

MenuState::MenuState() { }

void MenuState::handle(GameApp& app) {
    window = app.getWindow();

    init();

    // start main loop
    while(window->isOpen()) {
        
		tElapsed = clock.getElapsedTime();
		timeElapsed += tElapsed.asMilliseconds();
		clock.restart();
		
		// process events
        sf::Event event;
        
        while(window->pollEvent(event)) {
            // Exit
            if(event.type == sf::Event::Closed) {
                window->close();
            }
            if(event.type == sf::Event::LostFocus) {
                // loop until we get the GainedFocus event. Wait for the event so the thread can sleep and not use CPU.
                while(event.type != sf::Event::GainedFocus) {
                    window->waitEvent(event);
                    
                    // draw in case the screen was resized or another window was placed on top before
                    drawMenu();
                }

            }

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Up) {
                    selectPrevButton();
                }
                if(event.key.code == sf::Keyboard::Down) {
                    selectNextButton();
                }
                if(event.key.code == sf::Keyboard::Return) {
                    selectButton(app);
                }
            }
        }
		window->clear(sf::Color::White);
		drawBackground();
        drawMenu();
    }

}

void MenuState::init(){

    if (!font.loadFromFile(FONT_FILENAME)) {
        fprintf(stderr, "Error: Unable to load font. Program exiting\n");
        std::exit(-1);
    }

    numButtons = 2;

    arachineText.setFont(font);
    arachineText.setCharacterSize(70);
    arachineText.setPosition(250, 15);
    arachineText.setColor(sf::Color::White);
    arachineText.setString("Arachine");

    survivalText.setFont(font);
    survivalText.setCharacterSize(35);
    survivalText.setPosition(325, 150);
    survivalText.setColor(sf::Color::Red);
    survivalText.setString("Survival");

    //campaignText.setFont(font);
    //campaignText.setCharacterSize(35);
    //campaignText.setPosition(325, 250);
    //campaignText.setColor(sf::Color::Black);
    //campaignText.setString("Campaign");

    quitText.setFont(font);
    quitText.setCharacterSize(35);
    quitText.setPosition(325, 250);
    quitText.setColor(sf::Color::Black);
    quitText.setString("Quit"); 
    
	//Music
	if (!mBuffer.loadFromFile(MUSIC_FILENAME))
		fprintf(stderr, "Error: Unable to load menu music.\n");
	menuMusic.setBuffer(mBuffer);
	menuMusic.play();
	menuMusic.setPlayingOffset(sf::seconds(0));
	menuMusic.setLoop(true);
	
	//Background
	timeElapsed = 0;
	displacement = 0;
	//Why can't this take game.level.tileLength?
	if (!tileView.init(LEVEL_TILE_SHEET_FILENAME, 256, 256)) {
        fprintf(stderr, "Error: Unable to load level tile sheet. Program exiting\n");
        std::exit(-1);
    }
	tileView.updateSprite(0);
}

void MenuState::selectPrevButton(){
    if(curSelected == 0) { curSelected = (numButtons - 1); } else {
        curSelected = curSelected - 1;
    }
}

void MenuState::selectNextButton(){
    curSelected = (curSelected + 1) % numButtons;
}

void MenuState::selectButton(GameApp& app){
    switch(curSelected) {
        case 0:
			menuMusic.stop();
            app.goSurvival();
            app.run();
            break;
       // case 1:
			//menuMusic.stop();
            //app.goCampaign();
            //app.run();
            break;
        case 1:
	        menuMusic.stop();
            window->close();
            app.quit();
            break;
    }
}

void MenuState::drawBackground() {
	window->clear();
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 3; j++) {
			//Can't use Game::TILE_SIZE?
			tileView.position = (sf::Vector2f(i * 256 + displacement, j * 256));
			tileView.draw(window);
		}
	}
	if (timeElapsed > 1) {
		displacement = (displacement - 1) % 256;
		timeElapsed = 0;
	}
}

void MenuState::drawMenu(){
    switch(curSelected) {
        case 0:
            survivalText.setColor(sf::Color::Red);
            campaignText.setColor(sf::Color::Black);
            quitText.setColor(sf::Color::Black);
            break;
        //case 1:
         //   survivalText.setColor(sf::Color::Black);
          //  campaignText.setColor(sf::Color::Red);
          //  quitText.setColor(sf::Color::Black);
          //  break;
        case 1:
            survivalText.setColor(sf::Color::Black);
            campaignText.setColor(sf::Color::Black);
            quitText.setColor(sf::Color::Red);
            break;
    }
    
    //window->clear(sf::Color::White);
    window->draw(survivalText);
    window->draw(campaignText);
    window->draw(quitText);
    window->draw(arachineText);
    window->display();
}
