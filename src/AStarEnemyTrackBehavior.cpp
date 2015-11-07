#include "AStarEnemyTrackBehavior.hpp"
#include "Utils.hpp"
#include "Game.hpp"
#include "PathVertex.hpp"
#include <list>
#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>

static sf::Vector2f tempA(0.0f, 0.0f);
static sf::Vector2f tempB(0.0f, 0.0f);

template <class T> class PriorityLocation {
    public:
        typedef std::pair<T, float> PLElement;
        std::priority_queue<PLElement, std::vector<PLElement>,  std::greater<PLElement>> elements;

        bool isEmpty() { return elements.empty(); }
        void push(T node, float priority) {
            elements.emplace(node, priority);
        }
        const T pop() {
            PLElement ele = elements.top();
            elements.pop();
            return ele.first;
        }
};

PathVertexP aStarNext(const PathVertexAdjList& adjList, PathVertexP start, PathVertexP dest);

// this really shouldn't be taking in a game object
TrackNode AStarEnemyTrackBehavior::track(const Game& state, const sf::Vector2f& myPos, const sf::Vector2f& playerPos, PathVertexP myNode, PathVertexP destNode) {

    PathVertexP next = aStarNext(state.level.pathVertices, myNode, destNode);

    sf::Vector2f direction = myPos - next->position;
    //normalizeVector2f(direction);

    TrackNode tn;
    //tn.node = cmpVector2f(node, *next, TRACKNODE_EPISLON) ? &node : 0;
    //tn.direction = direction;
    return tn;
}

float aStarH(PathVertexP a, PathVertexP b) {
    //stub
    return 0.0;
}


PathVertexP aStarNext(const PathVertexAdjList& adjList, PathVertexP start, PathVertexP dest) {

    std::unordered_map<PathVertexP, PathVertexP> location_source;
    std::unordered_map<PathVertexP, float> costs;

    PriorityLocation<PathVertexP> pQueue;

    pQueue.push(start, 0);
    location_source[start] = start;
    costs[start] = 0;

    const int maxSteps = 40;
    int steps = 0;

    while (!pQueue.isEmpty() && steps++ < maxSteps) {
        PathVertexP u = pQueue.pop();

        //std::cout << u->position.x << "," << u->position.y << std::endl;

        std::list<PathVertexP> reachable;
        for (auto& neighbor : u->neighbors) {
            reachable.push_back(neighbor);
        }

        auto edgeCost = [&] (PathVertexP from , PathVertexP to) {
            //assumes grid-like structure
            return 1.0;
        };

        for (auto& v : reachable) {
            float f = costs[u] + edgeCost(u, v);
            costs[v] = f;
            float priority = f + aStarH(v, dest);
            pQueue.push(v, priority);
            location_source[v] = u;
        }
    }
    return dest;
}

#if 0
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

        for (auto& v : reachable) {
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
#endif
