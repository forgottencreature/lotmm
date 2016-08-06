#include <iostream>
#include "TileFloor.hpp"

TileFloor::TileFloor(Type t)
{
    switch(t)
    {
        case EMPTY:
            this->color = sf::Color::Transparent;
            this->health = 0;
            break;
        case DIRT:
            this->color = sf::Color(160,82,45);
            this->health = 100;
            break;
        case SNOW:
            this->color = sf::Color(25,25,112,255);
            this->health = 100;
            break;
        case GRASS:
            this->color = sf::Color::Green;
            this->health = 100;
            break;
        default:
            this->color = sf::Color::Transparent;
            this->health = 0;

    }
}

TileFloor::~TileFloor()
{

}

void TileFloor::setColor(sf::Color c)
{
    this->color = c;
}

sf::Color TileFloor::getColor()
{
    return this->color;
}

void TileFloor::setHealth(int h)
{
    this->health = h;
}

int TileFloor::getHealth()
{
    return this->health;
}