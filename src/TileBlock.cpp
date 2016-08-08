#include <iostream>
#include "TileBlock.hpp"

TileBlock::TileBlock()
{

}

TileBlock::~TileBlock()
{

}

void TileBlock::setType(Type b)
{

    switch(b)
    {
        case EMPTY:
            this->color = sf::Color::Transparent;
            this->health = 0;
            this->passThrough = true;
            break;
        default:
            this->color = sf::Color::Transparent;
            this->health = 0;
            this->passThrough = true;
    }

}

void TileBlock::setColor(sf::Color c)
{
    this->color = c;
}

sf::Color TileBlock::getColor()
{
    return this->color;
}

void TileBlock::setHealth(int h)
{
    this->health = h;
}

int TileBlock::getHealth()
{
    return this->health;
}

bool TileBlock::canPassThrough()
{
    return this->passThrough;
}