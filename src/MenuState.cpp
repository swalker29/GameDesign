#include "MenuState.hpp"
#include "GameApp.hpp"

static const std::string FONT_FILENAME = "assets/DroidSans.ttf";

MenuState::MenuState() { }

void MenuState::handle(GameApp& app) {
    window = app.getWindow();

    init();

    // start main loop
    while(window->isOpen()) {
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
                    draw();
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

        draw();
    }

}

void MenuState::init(){

    if (!font.loadFromFile(FONT_FILENAME)) {
        fprintf(stderr, "Error: Unable to load font. Program exiting\n");
        std::exit(-1);
    }

    numButtons = 3;

    arachineText.setFont(font);
    arachineText.setCharacterSize(70);
    arachineText.setPosition(50, 15);
    arachineText.setColor(sf::Color::Blue);
    arachineText.setString("Escape from Arachine");

    survivalText.setFont(font);
    survivalText.setCharacterSize(35);
    survivalText.setPosition(325, 150);
    survivalText.setColor(sf::Color::Red);
    survivalText.setString("Survival");

    campaignText.setFont(font);
    campaignText.setCharacterSize(35);
    campaignText.setPosition(325, 250);
    campaignText.setColor(sf::Color::Black);
    campaignText.setString("Campaign");

    quitText.setFont(font);
    quitText.setCharacterSize(35);
    quitText.setPosition(325, 350);
    quitText.setColor(sf::Color::Black);
    quitText.setString("Quit"); 
    
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
            app.goSurvival();
            app.run();
            break;
        case 1:
            //app.goCampaign();
            //app.run();
            break;
        case 2:
            window->close();
            app.quit();
            break;
    }
}

void MenuState::draw(){
    switch(curSelected) {
        case 0:
            survivalText.setColor(sf::Color::Red);
            campaignText.setColor(sf::Color::Black);
            quitText.setColor(sf::Color::Black);
            break;
        case 1:
            survivalText.setColor(sf::Color::Black);
            campaignText.setColor(sf::Color::Red);
            quitText.setColor(sf::Color::Black);
            break;
        case 2:
            survivalText.setColor(sf::Color::Black);
            campaignText.setColor(sf::Color::Black);
            quitText.setColor(sf::Color::Red);
            break;
    }
    
    window->clear(sf::Color::White);
    window->draw(survivalText);
    window->draw(campaignText);
    window->draw(quitText);
    window->draw(arachineText);
    window->display();
}
