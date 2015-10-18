#ifndef CONTROLSCONFIG_HPP
#define CONTROLSCONFIG_HPP

#include <stdio.h>
//add an include for the mapping

class ControlsConfig {
    public:
        //things which must be tracked to determine player control configuration
        int up, down, left, right, fireGun, prevWeapon, nextWeapon;
        float deadZoneMin, deadZoneMax, deadZoneMinValue, mouseSensitivity;
        bool useMouseWheelWeaponSwap, useController;
    
        ControlsConfig();
        
        bool loadControlsConfig(const char* controlsFilePath);
    
    private:
     
        void parseControlsConfig(FILE* controlsFile);
};
#endif
