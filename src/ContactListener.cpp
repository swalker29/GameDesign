#include "ContactListener.hpp"

#include "Character.hpp"
#include "ICollidable.hpp"
#include "ProjectileInstance.hpp"

ContactListener::ContactListener(std::vector<Projectile>* projectiles) : projectiles(projectiles) {

}

// Default destructor

void ContactListener::BeginContact(b2Contact* contact) {
    // stub
} 
 
void ContactListener::EndContact(b2Contact* contact) {
    // stub
} 
 
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    // detect all bullet collisions
    ICollidable* aUserData = static_cast<ICollidable*>(contact->GetFixtureA()->GetUserData());
    ICollidable* bUserData = static_cast<ICollidable*>(contact->GetFixtureB()->GetUserData());
    
    Character* character = nullptr;
    ProjectileInstance* projectile = nullptr;
        
    
    if (aUserData != nullptr) {
        if (aUserData->collisionType == ICollidable::CollisionType::CHARACTER) {
            character = static_cast<Character*>(aUserData);
        }
        else if (aUserData->collisionType == ICollidable::CollisionType::PROJECTILE) {
            projectile = static_cast<ProjectileInstance*>(aUserData);
        }
    }
    
    if (bUserData != nullptr) {
        if (bUserData->collisionType == ICollidable::CollisionType::CHARACTER) {
            character = static_cast<Character*>(bUserData);
        }
        else if (bUserData->collisionType == ICollidable::CollisionType::PROJECTILE) {
            projectile = static_cast<ProjectileInstance*>(bUserData);
        }
    }
    
    if (projectile != nullptr) {
        // projectile->impact(character);
        projectile->collided = true;
        contact->SetRestitution(0.0f);
    }
    else {
        if (aUserData != nullptr && bUserData != nullptr) {
            printf("A: %p       B: %p\n", aUserData, bUserData);
            printf("CHAR: %d    PROJ: %d\n\n", character == nullptr ? 0:1, projectile == nullptr ? 0:1);
        }
    }    
}
 
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    // stub
}
