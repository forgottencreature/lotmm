#ifndef TILEFLOOR_HPP
#define TILEFLOOR_HPP

#include <SFML/Graphics.hpp>

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

    std::string getIdentity();

    std::string identifier;

private:
    sf::Color color;
    int health;
};

#endif // TILEFLOOR_HPP