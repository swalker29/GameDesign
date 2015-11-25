#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <SFML/System/Vector2.hpp>

// struct so all members are public by default
struct InputData {
    sf::Vector2f movement;
    sf::Vector2f aim;
    bool fireWeapon;
    int weaponChange;
    // somethings for weapon change    
};
#endif
