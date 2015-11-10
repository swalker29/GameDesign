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

TrackNode AStarEnemyTrackBehavior::track(const Game& state, const sf::Vector2f& myPos, const sf::Vector2f& playerPos, PathVertexP myNode, PathVertexP destNode) {

    PathVertexP next = aStarNext(state.level.pathVertices, myNode, destNode);

    TrackNode tn;

    //tn.node = cmpVector2f(myPos, next->position, TRACKNODE_EPISLON) ? next : myNode;
    tn.node = next;

    sf::Vector2f direction = myPos - next->position;
    normalizeVector2f(direction);
    tn.direction = direction;

    return tn;
}

float aStarH(PathVertexP a, PathVertexP b) {
    //Manhattan distance
    return std::fabs(a->position.x - b->position.x) + std::fabs(a->position.y - b->position.y);
}


PathVertexP aStarNext(const PathVertexAdjList& adjList, PathVertexP start, PathVertexP dest) {

    std::unordered_map<PathVertexP, PathVertexP> location_source;
    std::unordered_map<PathVertexP, float> costs;

    PriorityLocation<PathVertexP> pQueue;

    pQueue.push(start, 0);
    location_source[start] = start;
    PathVertexP last = start;
    costs[start] = 0;

    //const int maxSteps = ;
    int steps = 0;

    while (!pQueue.isEmpty()) {
        PathVertexP u = pQueue.pop();


        std::list<PathVertexP> reachable;
        for (auto& neighbor : u->neighbors) {
            reachable.push_back(neighbor);
            //std::cout << neighbor->position.x << "," << neighbor->position.y << std::endl;
        }

        auto edgeCost = [&] (PathVertexP from , PathVertexP to) {
            return 4.0;
        };

        for (auto& v : reachable) {
            float f = costs[u] + edgeCost(u, v);
            if (costs.find(v) == costs.end() || f < costs[v]) {
                costs[v] = f;
                float priority = f + aStarH(v, dest);
                pQueue.push(v, priority);
                location_source[v] = u;
                last = v;
            }
        }
    }
    PathVertexP next;
    while (last != start) {
        next = last;
        last = location_source[last];
    }
    //std::cout << "(" << next->position.x << "," << next->position.y << ")" << std::endl;
    return next;
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
