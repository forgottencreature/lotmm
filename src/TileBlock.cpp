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
            this->color = sf::Color(60,60,100);
            this->health = 125;
            this->passThrough = false;
						this->hardness = 0.9;
            break;
        case PEAT:
            this->color = sf::Color(100,60,60);
            this->health = 100;
            this->passThrough = false;
						this->hardness = 1;
            break;
        case DIRT:
            this->color = sf::Color(60,100,60);
            this->health = 50;
            this->passThrough = false;
						this->hardness = 0.5;
            break;
        case SAND:
            this->color = sf::Color(100,100,60);
            this->health = 50;
            this->passThrough = false;
						this->hardness = 0.85;
            break;
        default:
            this->color = sf::Color::Transparent;
            this->health = 0;
            this->passThrough = true;
						this->hardness = 1;
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
