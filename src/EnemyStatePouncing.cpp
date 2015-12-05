#include "EnemyStatePouncing.hpp"
#include "LinearEnemyTrackBehavior.hpp"
#include "Enemy.hpp"
#include "Game.hpp"

EnemyStatePouncing::EnemyStatePouncing() :
    primeSpeed(2),
    pounceSpeed(6) {}

EnemyStatePouncing::EnemyStatePouncing(float primeSpeed, float pounceSpeed) :
    primeSpeed(primeSpeed),
    pounceSpeed(pounceSpeed)
{}

void EnemyStatePouncing::handle(Game& state, Enemy& enemy) {

    PathVertexP targetNode = state.player.node;
    if (enemy.node && enemy.node != targetNode && this->outRange) {
        this->changeState(enemy, this->outRange);
        return;
    }

    const float primeTime = 0.75f;
    static LinearEnemyTrackBehavior ltb;
    sf::Vector2f target = state.player.position;

    TrackNode tn = ltb.track(state, enemy.position, target, enemy.node, targetNode);

    if (enemy.timer.getElapsedTime().asSeconds() < primeTime) {
        enemy.speed = this->primeSpeed;
        tn.direction = tn.direction * -1.0f;
    } else {
        enemy.speed = this->pounceSpeed;
    }
    enemy.tracking = tn;
}
