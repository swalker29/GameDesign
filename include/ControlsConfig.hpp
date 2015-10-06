#ifndef CONTROLSCONFIG_HPP
#define CONTROLSCONFIG_HPP

#include <stdio.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <InputData.hpp>
//add an include for the mapping

class ControlsConfig {
    public:
        //things which must be tracked to determine player control configuration

        InputData input;
        int up, down, left, right, fireGun, prevWeapon, nextWeapon;
        float deadZoneMin, deadZoneMax, deadZoneMinValue, mouseSensitivity;
        bool useMouseWheelWeaponSwap, useController;
    
        ControlsConfig();
        
        bool loadControlsConfig(char* controlsFilePath);

        void getInput(bool useController, sf::RenderWindow* windowPointer);
        sf::RenderWindow* window;
    
    private:
        void parseControlsConfig(FILE* controlsFile);
        std::string parseInputIntoString(char* input);
        void getControllerInput();
        void getMouseAndKeyboardInput();
};
#endif
