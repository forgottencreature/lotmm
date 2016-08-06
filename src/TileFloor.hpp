#ifndef TILEFLOOR_HPP
#define TILEFLOOR_HPP

class TileFloor
{
public:
    enum Type { EMPTY, GRASS, DIRT, SNOW };

    TileFloor(TileFloor::Type t);
    virtual ~TileFloor();

    void setColor(sf::Color c);
    sf::Color getColor();

    void setHealth(int h);
    int getHealth();

private:
    sf::Color color;
    int health;
};

#endif // TILEFLOOR_HPP