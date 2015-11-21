#include "Character.hpp"

Character::Character(float health, Team team) : ICollidable(ICollidable::CollisionType::CHARACTER), health(health), team(team) {
}

// Default destructor
