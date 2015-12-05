#ifndef CONTACTLISTENER_HPP
#define CONTACTLISTENER_HPP

#include <vector>

#include <Box2D/Box2D.h>

#include "Player.hpp"
#include "Projectile.hpp"


class ContactListener : public b2ContactListener { 
    public: 
        // does not own these
        std::vector<Projectile>* projectiles;
        std::list<std::unique_ptr<Enemy>>* enemies;
        Player& player;
    
        ContactListener(std::vector<Projectile>* projectiles, std::list<std::unique_ptr<Enemy>>* enemies, Player& player);
        
        // Default destructor   
    
        // Box2D listener functions
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
        
    private:
        void checkTeamsAndDamagePlayer(Character* a, Character* b);
};

#endif
