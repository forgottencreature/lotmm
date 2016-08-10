#ifndef TILEFLOOR_HPP
#define TILEFLOOR_HPP

#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class Tile;

class TileFloor
{
public:
    enum Type { EMPTY, GRASS, DIRT, SNOW };

    TileFloor();
    virtual ~TileFloor();

    void setType(Type t);
    void setColor(sf::Color c);
    sf::Color getColor();

    void setHealth(int h);
    int getHealth();

    bool canPassThrough();

private:
    sf::Color color;
    int health;
    bool passThrough;
};

#endif // TILEFLOOR_HPP