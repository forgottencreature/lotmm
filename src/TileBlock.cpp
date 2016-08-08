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
        case STONE:
            this->color = sf::Color(28,128,128);
            this->health = 200;
            this->passThrough = false;
            break;
        case PEAT:
            this->color = sf::Color(205,133,63);
            this->health = 100;
            this->passThrough = false;
        case DIRT:
            this->color = sf::Color(139,69,19);
            this->health = 50;
            this->passThrough = false;
        case SAND:
            this->color = sf::Color(255,222,173);
            this->health = 50;
            this->passThrough = false;
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