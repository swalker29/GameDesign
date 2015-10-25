#include "Player.hpp"

static constexpr float PLAYER_COLLISION_RADIUS = 0.5f; // Box2D units so in meters

Player::Player() : position(0.0f, 0.0f), direction(1.0f, 0.0f) {
    circle.m_p.Set(0.0f, 0.0f);
    circle.m_radius = 0.5f;
}

// Default destructor
