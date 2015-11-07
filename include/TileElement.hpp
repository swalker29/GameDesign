#ifndef TILEELEMENT_HPP
#define TILEELEMENT_HPP

class b2Body;
class b2Fixture;

// Essentially a C struct of a tile resource number and a rotation
class TileElement {
    public:
        int resource;
        int rotation;

        b2Body* b2body;
        b2Fixture* b2fixture;
};
#endif
