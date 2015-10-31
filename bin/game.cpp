#include "GameApp.hpp"

int main(int argc, char** argv) {
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Game", sf::Style::Titlebar | sf::Style::Close);

    GameApp game(window);
    game.run();

    return 0;
}
