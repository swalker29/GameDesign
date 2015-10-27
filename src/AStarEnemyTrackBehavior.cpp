#include "AStarEnemyTrackBehavior.hpp"
#include "Utils.hpp"
#include "Game.hpp"
#include <list>
#include <queue>
#include <vector>
#include <unordered_map>

class PriorityLocation {
    public:
        typedef std::pair<const sf::Vector2f*, float> PLElement;
        std::priority_queue<PLElement, std::vector<PLElement>,  std::greater<PLElement>> elements;

        bool isEmpty() { return elements.empty(); }
        void push(const sf::Vector2f* node, float priority) {
            elements.emplace(node, priority);
        }
        const sf::Vector2f* pop() {
            PLElement ele = elements.top();
            elements.pop();
            return ele.first;
        }
};

const sf::Vector2f* aStarNext(const Game& state, const sf::Vector2f& start, const sf::Vector2f& dest);

TrackNode AStarEnemyTrackBehavior::track(const Game& state, const sf::Vector2f& node, const sf::Vector2f& myPos, const sf::Vector2f& playerPos) {

    //need to calculate end node from player's position with respect to the Game
    const sf::Vector2f* dest = &state.meshPoints.back(); //stub
    const sf::Vector2f* next = aStarNext(state, node, *dest);

    sf::Vector2f direction = myPos - *next;
    normalizeVector2f(direction);

    TrackNode tn;
    tn.node = cmpVector2f(node, *next, TRACKNODE_EPISLON) ? &node : 0;
    tn.direction = direction;
    return tn;
}

float aStarH(const sf::Vector2f& a, const sf::Vector2f& b) {
    //stub
    return 0.0;
}


const sf::Vector2f* aStarNext(const Game& state, const sf::Vector2f& start, const sf::Vector2f& dest) {

    std::unordered_map<const sf::Vector2f*, const sf::Vector2f*> location_source;
    std::unordered_map<const sf::Vector2f*, float> costs;
    PriorityLocation pQueue;

    pQueue.push(&start, 0);
    location_source[&start] = &start;
    costs[&start] = 0;

    while (!pQueue.isEmpty()) {
        auto u = pQueue.pop();

        std::list<const sf::Vector2f*> reachable;
        reachable.push_back(&dest);

        auto edgeCost = [&] (const sf::Vector2f* from, const sf::Vector2f* to) {
            return 1.0;
        };

        for (auto v : reachable) {
            float f = costs[u] + edgeCost(u, v);
            if (costs.find(v) == costs.end() || f < costs[v]) {
                costs[v] = f;
                float priority = f + aStarH(*v, dest);
                pQueue.push(v, priority);
                location_source[v] = u;
            }
        }
    }

    return &dest;
}
