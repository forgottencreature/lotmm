#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>

class TileMap;

class Player
{
public:
    Player();
    virtual ~Player();

    //enum Dir {UP, DOWN, LEFT, RIGHT};

    void setGridPosition(int newGridX, int newGridY, TileMap* m);
    void move(std::string dir);
    sf::RectangleShape get();

    void update(TileMap* m, float t);

    sf::Vector2f getSpritePosition();
    sf::Vector2<int> getGridPosition();
    sf::Vector2<int> getPreviousGridPosition();

    int gridX = 1, gridY = 1;

    int const damagePerTick = 10;

private:
    float speed = 3.0f;
    float x, y;

    void create();
    void checkBounds();
    void setSpritePosition(sf::Vector2f pos);
    void checkTileCollision(TileMap* m);

    bool const isMoving();

    sf::Vector2f getCoors();
    sf::Vector2<int> previousGridPosition;
    sf::RectangleShape playerSprite;
};

#endif // PLAYER_HPP