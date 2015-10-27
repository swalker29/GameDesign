#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <functional>

inline void normalizeVector2f(sf::Vector2f& v) {
    float lengthSquared = v.x*v.x + v.y*v.y;
    
    if (lengthSquared != 0.0f) {
        float length = std::sqrt(lengthSquared);
        v.x /= length;
        v.y /= length;
    }
}    

//returns True if two vectors are mostly the same
inline bool cmpVector2f(const sf::Vector2f& a, const sf::Vector2f& b, float epsilon) {
    sf::Vector2f res = a - b;
    if (std::fabs(res.x) > epsilon) return false;
    if (std::fabs(res.y) > epsilon) return false;
    return true;
}
#endif
