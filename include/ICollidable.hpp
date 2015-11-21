#ifndef ICOLLIDABLE_HPP
#define ICOLLIDABLE_HPP

class ICollidable {
    public:
        enum CollisionType { PROJECTILE, CHARACTER };
        
        CollisionType collisionType;
        
        ICollidable(CollisionType collisionType);
        
        // Default destructor        
};
#endif
