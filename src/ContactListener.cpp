#include "ContactListener.hpp"

#include "Character.hpp"
#include "ICollidable.hpp"
#include "ProjectileInstance.hpp"

static constexpr float HIGH_VELOCITY_THRESHOLD = 40.0f;
static constexpr float HIGH_DAMAGE_FACTOR = 0.003f;
static constexpr float LOW_VELOCITY_THRESHOLD_BOTTOM = 0.9f;
static constexpr float LOW_VELOCITY_THRESHOLD_TOP = 5.0f;
static constexpr float LOW_DAMAGE_FACTOR = 0.1f;

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
    Character* characterB = nullptr;
    ProjectileInstance* projectile = nullptr;
    
    bool aIsCharacter = false;        
    
    if (aUserData != nullptr) {
        if (aUserData->collisionType == ICollidable::CollisionType::CHARACTER) {
            character = static_cast<Character*>(aUserData);
            aIsCharacter = true;
        }
        else if (aUserData->collisionType == ICollidable::CollisionType::PROJECTILE) {
            projectile = static_cast<ProjectileInstance*>(aUserData);
        }
    }
    
    if (bUserData != nullptr) {
        if (bUserData->collisionType == ICollidable::CollisionType::CHARACTER) {
            if (aIsCharacter) {
                characterB = static_cast<Character*>(bUserData);
                checkTeamsAndDamagePlayer(character, characterB);
            }
            else {
                character = static_cast<Character*>(bUserData);
            }
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

void ContactListener::checkTeamsAndDamagePlayer(Character* a, Character* b) {
    Player* player = nullptr;
    Enemy* enemy = nullptr;
    
    if (a->team == Character::Team::HUMAN) {
        player = static_cast<Player*>(a);
        enemy = static_cast<Enemy*>(b);
    }
    else if (a->team == Character::Team::HUMAN) {
        player = static_cast<Player*>(b);
        enemy = static_cast<Enemy*>(a);
    }
    
    if (player != nullptr) {
        b2Vec2 playerVel = player->b2body->GetLinearVelocity();
        b2Vec2 enemyVel = enemy->b2body->GetLinearVelocity();
        b2Vec2 diff = playerVel - enemyVel;
        float velSq = diff.x*diff.x + diff.y*diff.y;
        
        if (velSq > HIGH_VELOCITY_THRESHOLD) {
            player->health -= velSq * HIGH_DAMAGE_FACTOR;
        }
        else if (velSq > LOW_VELOCITY_THRESHOLD_BOTTOM && velSq < LOW_VELOCITY_THRESHOLD_TOP) {
            player->health -= velSq * LOW_DAMAGE_FACTOR;
        }
    }
}
