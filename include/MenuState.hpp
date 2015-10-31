#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "AppState.hpp"

class GameApp;

class MenuState : public AppState {
    public:
        MenuState();
        void handle(GameApp& gameApp);
};

#endif
