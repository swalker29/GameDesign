#include "ContactListener.hpp"

#include "Character.hpp"
#include "ICollidable.hpp"
#include "ProjectileInstance.hpp"

ContactListener::ContactListener(std::vector<Projectile>* projectiles, std::list<std::unique_ptr<Enemy>>* enemies, Player& player) : projectiles(projectiles), enemies(enemies), player(player) {

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
        (*projectiles)[projectile->projectileIndex].impact(*projectile, player, enemies, character);
        projectile->collided = true;
        contact->SetRestitution(0.0f);
    }   
}
 
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
    // stub
}
