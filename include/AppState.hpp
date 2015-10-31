#ifndef APPSTATE_HPP
#define APPSTATE_HPP

#include "GameApp.hpp"
class AppState{
    public:
        virtual ~AppState(){}
        virtual void handle(GameApp& app){};
};

#endif
