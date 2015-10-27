#include "LinearEnemyTrackBehavior.hpp"
#include "Utils.hpp"

TrackNode LinearEnemyTrackBehavior::track(const Game& state, const sf::Vector2f& node, const sf::Vector2f& myPos, const sf::Vector2f& playerPos) {
    sf::Vector2f newVec = myPos - playerPos;
    normalizeVector2f(newVec);
    TrackNode tn;
    tn.node = NULL;
    tn.direction = newVec;
    return tn;
}
