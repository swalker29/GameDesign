#include "LinearEnemyTrackBehavior.hpp"
#include "Utils.hpp"

TrackNode LinearEnemyTrackBehavior::track(const Game& state, const sf::Vector2f& myPos, const sf::Vector2f& playerPos, PathVertexP myNode, PathVertexP destNode) {
    sf::Vector2f newVec = playerPos - myPos;
    normalizeVector2f(newVec);
    TrackNode tn;
    tn.node = myNode;
    tn.direction = newVec;
    return tn;
}
