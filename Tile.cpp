#include <iostream>
#include <math.h>
#include "Tile.hpp"

Tile::Tile()
{

}

Tile::~Tile()
{

}

void Tile::setPosition(sf::Vector2<int> p) 
{
    Tile::position = p;
}

void Tile::setPosition(int x, int y) 
{
    Tile::position = sf::Vector2<int>(x, y);
}


void Tile::setType(Type t) 
{
    Tile::type = t;
}

void Tile::removeHealth(int i) 
{
    this->health = this->health - i;
}

Tile::Type Tile::getType() 
{
    return Tile::type;
}

sf::Vector2<int> Tile::getPosition() 
{
    return Tile::position;
}

int Tile::getX() 
{
    return Tile::position.x;
}

int Tile::getY() 
{
    return Tile::position.y;
}