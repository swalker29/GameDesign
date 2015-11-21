#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICollidable.hpp"

class Character : public ICollidable {
    public:    
        enum Team { HUMAN, ENEMY };
    
        float health;
        Team team;
        
        Character(float health, Team team);
        
        // Default destructor
};
#endif
