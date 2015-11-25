#include "ControlsConfig.hpp"

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <KeyMap.hpp>
#include "Utils.hpp"

ControlsConfig::ControlsConfig() : changeWeaponsReleased(true) {

}

/*
* Loads the configuration file where user-specific control configuration resides.
* Returns false if it fails. Otherwise, it parses the file to store the data in
* usable form and closes the file, then returns true.
*/
bool ControlsConfig::loadControlsConfig(const char* controlsFilePath) {
    FILE* controlsFile = fopen(controlsFilePath, "r");
	
    if (NULL == controlsFile) {
        return false;
    }
    
	parseControlsConfig(controlsFile);
	
	fclose(controlsFile);
	
	return true;
}

/*
* Loads the configuration file where user-specific control configuration resides.
* Returns false if it fails. Otherwise, it parses the file to store the data in
* usable form and closes the file, then returns true.
*/
bool ControlsConfig::loadControlsConfig(char* controlsFilePath){
    FILE* controlsFile = fopen(controlsFilePath, "r");
	
    if (NULL == controlsFile) {
        return false;
    }
    
	parseControlsConfig(controlsFile);
	
	fclose(controlsFile);
	
	return true;
}

/*
* Turns char input into string output, which will later be compared.
*
*
*/
std::string ControlsConfig::parseInputIntoString(char* input){
    std::string returnString;
    returnString = std::string(input);
    returnString = returnString.substr(0, returnString.size()-1); //need to remove terminating character from string
    return returnString;
}

/*
* The general idea here: read lines of config file. Lines are hardcoded to respective function.
* Map the string input to the correct int value associated with SFML enums.
*
*/
void ControlsConfig::parseControlsConfig(FILE* controlsFile) {
    char buf[256];
    int intBuf[3];
    float tempFloat;
    std::string tempInputStr;

    //helper to convert char array input into relevant int to be processed by SFML enums
    KeyMap kMap = KeyMap();
    kMap.createMap();

    //flags we're interested in
    bool useMouseWheelWeaponSwap = false;
    bool useController = false;
	
    //keybindings we're interested in
    up = -1;
    down = -1;
    left = -1;
    right = -1;
    fireGun = -1;
    prevWeapon = -1;
    nextWeapon = -1;
	
	//settings we're interested in, defaults
	deadZoneMin = 25;
	deadZoneMax = 100;
	deadZoneMinValue = 50;
	mouseSensitivity = 100;
	
	// while we have not reached the end of the controlsFile, read the next token

    /*
    * move past explanatory lines in config file
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);

    /*
    * check to see if we're using the controller
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    if(strcmp(buf, "t") == 0){
        useController = true;
    } //otherwise default false.

    /*
    * check to see if we're using mouse wheel to change weapons
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    if(strcmp(buf, "t") == 0){
        useMouseWheelWeaponSwap = true;
    } //otherwise default false.

    /*
    * get the up key
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    tempInputStr = std::string(buf);
    tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
    up = kMap.getKeyValue(tempInputStr); //yields correct value of up

    /*
    * get the down key
    */
	fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    tempInputStr = std::string(buf);
    tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
    down = kMap.getKeyValue(tempInputStr);
       
    /*
    * get the left key
    */
	fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    tempInputStr = std::string(buf);
    tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
    left = kMap.getKeyValue(tempInputStr);

    /*
    * get the right key
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    tempInputStr = std::string(buf);
    tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
    right = kMap.getKeyValue(tempInputStr);

    /*
    * get the fireGun key
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    tempInputStr = std::string(buf);
    tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
    fireGun = kMap.getKeyValue(tempInputStr);

    /*
    * get the previousWeapon key
    */
	fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    tempInputStr = std::string(buf);
    tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
    prevWeapon = kMap.getKeyValue(tempInputStr);

    /*
    * get the nextWeapon key
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    tempInputStr = std::string(buf);
    tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
    nextWeapon = kMap.getKeyValue(tempInputStr);
  
    /*
    * get the deadZoneMin
    */
    fgets(buf, sizeof(buf), controlsFile);
	fgets(buf, sizeof(buf), controlsFile);
    sscanf(buf, "%f", &deadZoneMin);

    /*
    * get the deadZoneMax
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    sscanf(buf, "%f", &deadZoneMax);

    /*
    * get the deadZoneMinValue
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    sscanf(buf, "%f", &deadZoneMinValue);

    /*
    * get the mouseSensitivity
    */
    fgets(buf, sizeof(buf), controlsFile);
    fgets(buf, sizeof(buf), controlsFile);
    sscanf(buf, "%f", &mouseSensitivity);
}

/*
* General function which splits input into two cases.
* If a controller is detected, we getControllerInput.
* Otherwise, we getMouseAndKeyboardInput.
*/
void ControlsConfig::getInput(bool useController, sf::RenderWindow* windowPointer) {
    window = windowPointer;
    if (useController) {
        getControllerInput();
    }
    else {
        getMouseAndKeyboardInput();
    }
}

/*
* Gets input from the controller and stores it in the input class data structure.
*
*
*/
void ControlsConfig::getControllerInput() {
    sf::Joystick::Axis verticalMoveAxis = sf::Joystick::Y;
    sf::Joystick::Axis horizontalMoveAxis = sf::Joystick::X;
    sf::Joystick::Axis verticalAimAxis = sf::Joystick::V;
    sf::Joystick::Axis horizontalAimAxis = sf::Joystick::U;
    
    // Need to test that these values are read properly
    float deadZoneRadius = deadZoneMin;
    float maxRadius = deadZoneMax;
    float aimDeadZoneRadius = deadZoneMinValue;
    
    // sanity check
    if (sf::Joystick::isConnected(0)) {
        
        unsigned int buttonCount = sf::Joystick::getButtonCount(0);
        
        for (int x = 0; x < buttonCount; x++) {
            if (sf::Joystick::isButtonPressed(0, x)) {
                //printf("Button %d is pressed\n", x);
            }
        }
    }

    // get movement vector (left thumbstick on xbox controller)
    float moveY = sf::Joystick::getAxisPosition(0, verticalMoveAxis);
    float moveX = sf::Joystick::getAxisPosition(0, horizontalMoveAxis);
    
    float length = sqrt(moveX*moveX + moveY*moveY);
    float factor = (length - deadZoneRadius) / (maxRadius - deadZoneRadius);
    
    sf::Vector2f moveVector(0.0f, 0.0f);
    
    if (factor > 0.0f) {
        // if the factor is larger than 1, scale back to make moveVector unit length
        if (factor > 1.0f) {
            factor = 1.0f / factor;
        }
        
        moveVector.x =  factor * moveX / maxRadius;
        moveVector.y = factor * moveY / maxRadius;
    }
    
    // get aim vector (right thumbstick on xbox controller)
    float aimY = sf::Joystick::getAxisPosition(0, verticalAimAxis);
    float aimX = sf::Joystick::getAxisPosition(0, horizontalAimAxis);
    
    length = sqrt(aimX*aimX + aimY*aimY);
    
    sf::Vector2f aimVector(0.0f, 0.0f);
    
    if (length > aimDeadZoneRadius) {
        aimVector.x = aimX;
        aimVector.y = aimY;
        
        normalizeVector2f(aimVector);
    }
    
    // set values in input
    //input.fireWeapon = sf::Joystick::getAxisPosition(fireAxis) > fireAxisThreshold;
    input.movement = moveVector;
    input.aim = aimVector;
}

/*
* Gets input from the mouse and keyboard and stores it in input data structure.
*
*
*/
void ControlsConfig::getMouseAndKeyboardInput() {
    sf::Keyboard::Key moveUp = static_cast<sf::Keyboard::Key>(up);
    sf::Keyboard::Key moveDown = static_cast<sf::Keyboard::Key>(down);
    sf::Keyboard::Key moveRight = static_cast<sf::Keyboard::Key>(right);
    sf::Keyboard::Key moveLeft = static_cast<sf::Keyboard::Key>(left);
    sf::Mouse::Button fireGun = sf::Mouse::Left;
    sf::Keyboard::Key next = static_cast<sf::Keyboard::Key>(nextWeapon);
    sf::Keyboard::Key previous = static_cast<sf::Keyboard::Key>(prevWeapon);
    
    // get movement vector from keyboard
    sf::Vector2f moveVector(0.0f, 0.0f);
    
    if (sf::Keyboard::isKeyPressed(moveDown)) {
        moveVector.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(moveUp)) {
        moveVector.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(moveRight)) {
        moveVector.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(moveLeft)) {
        moveVector.x -= 1.0f;
    }
    
    // get aim vector from mouse
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    sf::Vector2u windowSize = window->getSize();
    
    sf::Vector2f aimVector(mousePosition.x - (windowSize.x / 2.0f), mousePosition.y - (windowSize.y / 2.0f));
    
    // determine if to switch weapons
    if (!changeWeaponsReleased) {
        changeWeaponsReleased = !sf::Keyboard::isKeyPressed(next) && !sf::Keyboard::isKeyPressed(previous);
    }
    
    if (input.weaponChange != 0) {
        input.weaponChange = 0;
    }
    else if (changeWeaponsReleased) {
        int desiredChange = 0;
        
        if (sf::Keyboard::isKeyPressed(next)) {
            desiredChange++;
            changeWeaponsReleased = false;
        }
        if (sf::Keyboard::isKeyPressed(previous)) {
            desiredChange--;
            changeWeaponsReleased = false;
        }
        
        input.weaponChange = desiredChange;
    }

    normalizeVector2f(aimVector);
    normalizeVector2f(moveVector);
    
    // set values in input
    input.fireWeapon = sf::Mouse::isButtonPressed(fireGun);
    input.movement = moveVector;
    input.aim = aimVector;
}



