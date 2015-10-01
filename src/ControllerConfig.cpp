#include "InputConfig.hpp"

#include <stdlib.h>
#include <string.h>

InputConfig::InputConfig() {

}

// default destructor

bool Level::loadInputConfig(char* controllerFilePath) {
	FILE* controllerFile = fopen(controllerFilePath, "r");
	
	if (NULL == controllerFile) {
        return false;
    }
    
	parseInputConfig(controllerFile);
	
	fclose(controllerFile);
	
	return true;
}

/*
* The general idea here: if the first character in a line is "#" we ignore that as a comment.
* Otherwise, read in the line. Lines are hardcoded to their respective function, e.g.
* first line determines Up key, second line determines Down key, etc.
*/
void Level::parseInputConfig(FILE* controllerFile) {
	char buf[256];
	int intBuf[3];
	float tempFloat;
	
	//keybindings we're interested in
	int up = -1;
	int down = -1;
	int left = -1;
	int right = -1;
	int fireGun = -1;
	
	//settings we're interested in
	float deadZoneMin = 0;
	float deadZoneMax = 100;
	float deadZoneMinValue = 0;
	float mouseSensitivity = 10;
	
	// while we have not reached the end of the controllerFile, read the next token
	while(fscanf(controllerFile, "%s", buf) != EOF) {

		/*
		* get the up key
		*/
		fgets(buf, sizeof(buf), controllerFile);
		fgets(buf, sizeof(buf), controllerFile);
		if (strlen(buf) == 1){
		//means our input is a letter or number
			if ((buf >= '0') && (buf <= '9')) {
				up = buf - '0';
			} else if ((buf >= 'a') && (buf <= 'z')) {
				up = buf - 'a';
			}
		} else {
		//means our input is a special key
			
		}

		/*
		* get the down key
		*/

		/*
		* get the left key
		*/

		/*
		* get the right key
		*/

		/*
		* get the fireGun key
		*/

		/*
		* get the deadZoneMin
		*/

		/*
		* get the deadZoneMax
		*/

		/*
		* get the deadZoneMinValue
		*/

		/*
		* get the mouseSensitivity
		*/
		
		switch(buf[0]) {
			case "#":
			//comment case, skip the line
				fgets(buf, sizeof(buf), controllerFile);
			case default:
			//otherwise read the line
				fgets(buf, sizeof(buf), controllerFile);
				if (strlen(buf) == 1){
					
				}



				
			//
			case strlen: 
				fscanf(controllerFile, "%d", &intBuf[0]);
    			
    			// tileVector.resize(intBuf[0]);
			break;
			// 'u', uses tile definition
			case 'u': 
			    fscanf(controllerFile, "%d", &intBuf[0]);
				fgets(buf, sizeof(buf), controllerFile);
    			
    			buf[strlen(buf) - 1] = '\0';
    			
			break;
			// 'w', width, number of tiles in the X direction
			case 'w':
				fscanf(controllerFile, "%d", &width);
				
				if (height != -1) {
			        std::vector<TileElement> row(height);
			        
			        for (int x = 0; x < width; x++) {
                        tiles.push_back(row);
                    }
                }
			break;
			// 'h', height, number of tiles in the Y direction
			case 'h': 
				fscanf(controllerFile, "%d", &height);
			    
			    if (width != -1) {
			        std::vector<TileElement> row(height);
			        
			        for (int x = 0; x < width; x++) {
                        tiles.push_back(row);
                    }
                }   
			break;
			// 't', tile definition: x y tileResourceNum rotation
			case '#':
				fscanf(controllerFile, "%d %d %d %f", &intBuf[0], &intBuf[1], &intBuf[2], &tempFloat);
				tiles[intBuf[0]][intBuf[1]].resource = intBuf[2];
				tiles[intBuf[0]][intBuf[1]].rotation = tempFloat;
			break;
			// something else, ignore it
			default:
				fgets(buf, sizeof(buf), controllerFile);
			break;
		}
	}
}
