#include "ControlsConfig.hpp"

#include <stdlib.h>
#include <string.h>
#include <KeyMap.hpp>

ControlsConfig::ControlsConfig() {

}

// default destructor

bool Level::loadControlsConfig(char* controlsFilePath) {
    FILE* controlsFile = fopen(controlsFilePath, "r");
	
    if (NULL == controlsFile) {
        return false;
    }
    
	parseControlsConfig(controlsFile);
	
	fclose(controlsFile);
	
	return true;
}

/*
* The general idea here: if the first character in a line is "#" we ignore that as a comment.
* Otherwise, read in the line. Lines are hardcoded to their respective function, e.g.
* first line determines Up key, second line determines Down key, etc.
*/
void Level::parseControlsConfig(FILE* controlsFile) {
    char buf[256];
    int intBuf[3];
    float tempFloat;

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
	
	//settings we're interested in
	float deadZoneMin = 0;
	float deadZoneMax = 100;
	float deadZoneMinValue = 0;
	float mouseSensitivity = 10;
	
	// while we have not reached the end of the controlsFile, read the next token
	while(fscanf(controlsFile, "%s", buf) != EOF) {

        /*
        * move past explanatory lines
        */
        fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);

        /*
        * check to see if we're using the controller
        */
        fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if(buf == 't'){
            useController = true;
        } //otherwise default false.

        /*
        * check to see if we're using mouse wheel to change weapons
        */
        fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if(buf == 't'){
            useMouseWheelWeaponSwap = true;
        } //otherwise default false.

		/*
		* get the up key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= 'a') && (buf <= 'z')) {
            //make sure it's a letter
                up = buf - 'a';
            }
        } else {
		//means our input is a special key - we have to map it.
            up = kMap.getKeyValue(buf);
        }

		/*
		* get the down key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= 'a') && (buf <= 'z')) {
            //make sure it's a letter
                down = buf - 'a';
            }
        } else {
		//means our input is a special key - we have to map it.
            down = kMap.getKeyValue(buf);
        }

		/*
		* get the left key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= 'a') && (buf <= 'z')) {
            //make sure it's a letter
                left = buf - 'a';
            }
        } else {
		//means our input is a special key - we have to map it.
            left = kMap.getKeyValue(buf);
        }

		/*
		* get the right key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= 'a') && (buf <= 'z')) {
            //make sure it's a letter
                right = buf - 'a';
            }
        } else {
		//means our input is a special key - we have to map it.
            right = kMap.getKeyValue(buf);
        }

		/*
		* get the fireGun key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= 'a') && (buf <= 'z')) {
            //make sure it's a letter
                fireGun = buf - 'a';
            }
        } else {
		//means our input is a special key - we have to map it.
            fireGun = kMap.getKeyValue(buf);
        }

		/*
		* get the previousWeapon key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= 'a') && (buf <= 'z')) {
            //make sure it's a letter
                up = buf - 'a';
            }
        } else {
		//means our input is a special key - we have to map it.
            prevWeapon = kMap.getKeyValue(buf);
        }

		/*
		* get the nextWeapon key
		*/
	    fgets(buf, sizeof(buf), controlsFile);
        fgets(buf, sizeof(buf), controlsFile);
        if (strlen(buf) == 1){
        //means our input is a letter or number
            if ((buf >= 'a') && (buf <= 'z')) {
            //make sure it's a letter
                up = buf - 'a';
            }
        } else {
		//means our input is a special key - we have to map it.
            nextWeapon = kMap.getKeyValue(buf);
        }

		/*
		* get the deadZoneMin
		*/
        fgets(buf, sizeof(buf), controlsFile);
		fgets(buf, sizeof(buf), controlsFile);
        sscanf(buf, "%d", &deadZoneMin);
		/*
		* get the deadZoneMax
		*/
        fgets(buf, sizeof(buf), controlsFile);
		fgets(buf, sizeof(buf), controlsFile);
        sscanf(buf, "%d", &deadZoneMax);
		/*
		* get the deadZoneMinValue
		*/
        fgets(buf, sizeof(buf), controlsFile);
		fgets(buf, sizeof(buf), controlsFile);
        sscanf(buf, "%d", &deadZoneMinValue);
		/*
		* get the mouseSensitivity
		*/
        fgets(buf, sizeof(buf), controlsFile);
		fgets(buf, sizeof(buf), controlsFile);
        sscanf(buf, "%d", &mouseSensitivity);
        }
    }
}
