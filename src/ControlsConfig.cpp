#include "ControlsConfig.hpp"

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <KeyMap.hpp>

ControlsConfig::ControlsConfig() {

}

// default destructor

bool ControlsConfig::loadControlsConfig(char* controlsFilePath) {
    FILE* controlsFile = fopen(controlsFilePath, "r");
	
    if (NULL == controlsFile) {
        return false;
    }
    
	parseControlsConfig(controlsFile);
	
	fclose(controlsFile);
	
	return true;
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
    int up = -1;
    int down = -1;
    int left = -1;
    int right = -1;
    int fireGun = -1;
    int prevWeapon = -1;
    int nextWeapon = -1;
	
	//settings we're interested in, defaults
	float deadZoneMin = 25;
	float deadZoneMax = 100;
	float deadZoneMinValue = 50;
	float mouseSensitivity = 100;
	
	// while we have not reached the end of the controlsFile, read the next token
	while(fscanf(controlsFile, "%s", buf) != EOF) {

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
        if (strlen(buf) == 1){ //actually the length of buf when buf = a will be 2 due to closing char
        //means our input is a letter or number
            if ((buf >= "a") && (buf <= "z")) {
            //make sure it"s a letter
                up = buf - "a"; //doesn't work yet
            }
        } else {
		//means our input is a special key - we have to map it.
            tempInputStr = std::string(buf);
            tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
            up = kMap.getKeyValue(tempInputStr); //yields correct value of up
        }

		/*
		* get the down key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= "a") && (buf <= "z")) {
            //make sure it"s a letter
                down = buf - "a";
            }
        } else {
		//means our input is a special key - we have to map it.
            tempInputStr = std::string(buf);
            tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
            down = kMap.getKeyValue(tempInputStr);
        }

		/*
		* get the left key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= "a") && (buf <= "z")) {
            //make sure it"s a letter
                left = buf - "a";
            }
        } else {
		//means our input is a special key - we have to map it.
            tempInputStr = std::string(buf);
            tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
            left = kMap.getKeyValue(tempInputStr);
        }

		/*
		* get the right key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= "a") && (buf <= "z")) {
            //make sure it"s a letter
                right = buf - "a";
            }
        } else {
		//means our input is a special key - we have to map it.
            tempInputStr = std::string(buf);
            tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
            right = kMap.getKeyValue(tempInputStr);
        }

		/*
		* get the fireGun key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= "a") && (buf <= "z")) {
            //make sure it"s a letter
                fireGun = buf - "a";
            }
        } else {
		//means our input is a special key - we have to map it.
            tempInputStr = std::string(buf);
            tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
            fireGun = kMap.getKeyValue(tempInputStr);
        }

		/*
		* get the previousWeapon key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= "a") && (buf <= "z")) {
            //make sure it"s a letter
                up = buf - "a";
            }
        } else {
		//means our input is a special key - we have to map it.
            tempInputStr = std::string(buf);
            tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
            prevWeapon = kMap.getKeyValue(tempInputStr);
        }

		/*
		* get the nextWeapon key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= "a") && (buf <= "z")) {
            //make sure it"s a letter
                up = buf - "a";
            }
        } else {
		//means our input is a special key - we have to map it.
            tempInputStr = std::string(buf);
            tempInputStr = tempInputStr.substr(0, tempInputStr.size()-1); //need to remove terminating character from string
            nextWeapon = kMap.getKeyValue(tempInputStr);
        }

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
    }
