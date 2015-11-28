#include "EnemyStateFiring.hpp"
#include "Game.hpp"
#include "Enemy.hpp"
#include <iostream>
#include "Utils.hpp"
#include "ProjectileInstance.hpp"

#define DEBUGFIRING 1
EnemyStateFiring::EnemyStateFiring() : fireRate(1.5) {}
EnemyStateFiring::EnemyStateFiring(float shotInterval) : fireRate(shotInterval) {}

void EnemyStateFiring::setTransition(std::shared_ptr<EnemyState> outRange) {
    this->outRange = outRange;
}

void EnemyStateFiring::handle(Game& state, Enemy& enemy) {

    //if player moves away from the enemy's node, the enemy may reengage track behavior
    PathVertexP targetNode = state.player.node;
    if (enemy.node && enemy.node != targetNode && this->outRange) {
        enemy.state = this->outRange;
        return;
    }
    //Limits enemy fire rate
    if (enemy.timer.getElapsedTime().asSeconds() > fireRate) {

        sf::Vector2f playerDirection = state.player.position - enemy.position;
        normalizeVector2f(playerDirection);

        int pind = 0;
        std::unique_ptr<ProjectileInstance> missle(new ProjectileInstance(pind, enemy.position + 0.5f * playerDirection, playerDirection, &state.projectiles[pind].circle, state.getWorld()));

        sf::Vector2f vel = playerDirection * state.projectiles[pind].velocity;
        b2Vec2 velocity(vel.x, vel.y);

        missle->b2body->SetLinearVelocity(velocity);

        state.enemyProjectiles.push_back(std::move(missle));
#if DEBUGFIRING
        std::cout << "BANG!" << std::endl;
#endif
        enemy.timer.restart();
    }
}
