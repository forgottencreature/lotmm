#ifndef TILEBLOCK_HPP
#define TILEBLOCK_HPP

#include <SFML/Graphics.hpp>

class TileBlock
{
public:
    enum Type { EMPTY };

    TileBlock();
    virtual ~TileBlock();

    void setBlock(Type t);
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

#endif // TILEBLOCK_HPP