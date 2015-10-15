#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

inline void normalizeVector2f(sf::Vector2f& v) {
    float lengthSquared = v.x*v.x + v.y*v.y;
    
    if (lengthSquared != 0.0f) {
        float length = std::sqrt(lengthSquared);
        v.x /= length;
        v.y /= length;
    }
}    
#endif
