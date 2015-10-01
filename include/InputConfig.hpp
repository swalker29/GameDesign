#ifndef INPUTCONFIG_HPP
#define INPUTCONFIG_HPP

#include <stdio.h>
//add an include for the mapping

class InputConfig {
    public:
        
        int up, down, left, right, fireGun;
		float deadZoneMin, deadZoneMax, deadZoneMinValue, mouseSensitivity;
    
        InputConfig();
        
        bool loadInputConfig(char* inputFilePath);
    
    private:
     
        void parseInputConfig(FILE* inputFile);
};
#endif
