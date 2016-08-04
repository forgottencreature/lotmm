#ifndef TILE_HPP
#define TILE_HPP
#include <SFML/Graphics.hpp>

class Tile
{
public:
    /* 
    * Type will probably have to be refactored.
    * Different classes for different types, maybe? 
    */

    enum Type
    {
        empty,
        dirt,
        snow,
        grass,
    };
    
    Tile();
    virtual ~Tile();

    void setPosition(sf::Vector2<int> p);
    void setPosition(int x, int y);
    void setType(Type t);

    Type getType();
    sf::Vector2<int> getPosition();

    int getX();
    int getY();

    static const int HEIGHT = 16;
    static const int WIDTH = 16;
private:
    Type type;
    sf::Vector2<int> position;
};

#endif