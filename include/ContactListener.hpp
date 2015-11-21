#ifndef CONTACTLISTENER_HPP
#define CONTACTLISTENER_HPP

#include <vector>

#include <Box2D/Box2D.h>

#include "Projectile.hpp"

class ContactListener : public b2ContactListener { 
    public: 
        // does not own these
        std::vector<Projectile>* projectiles;
    
        ContactListener(std::vector<Projectile>* projectiles);
        
        // Default destructor   
    
        // Box2D listener functions
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif
