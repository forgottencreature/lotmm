#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>

#include "TileFloor.hpp"

class TileFloor;

class Tile
{
public:
    Tile();
    virtual ~Tile();

    void setPosition(sf::Vector2<int> p);
    void setPosition(int x, int y);
    void setFloor(TileFloor f);

    //void removeHealth(int i);

    TileFloor &getFloor();
    sf::Vector2<int> getPosition();

    int getX();
    int getY();

    static const int HEIGHT = 32;
    static const int WIDTH = 32;

private:
    sf::Vector2<int> position;
    TileFloor floor;
}; 

#endif