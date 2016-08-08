#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>

#include "TileFloor.hpp"
#include "TileBlock.hpp"

class TileFloor;
class TileBlock;

class Tile
{
public:
    Tile();
    virtual ~Tile();

    void setPosition(sf::Vector2<int> p);
    void setPosition(int x, int y);

    void setFloor(TileFloor f);
    void setBlock(TileBlock b);

    //void removeHealth(int i);

    TileFloor &getFloor();
    TileBlock &getBlock();

    sf::Vector2<int> getPosition();

    int getX();
    int getY();

    static const int HEIGHT = 32;
    static const int WIDTH = 32;

private:
    sf::Vector2<int> position;
    TileFloor floor;
    TileBlock block;
}; 

#endif