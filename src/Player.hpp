#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>

class TileMap;

class Player{
public:
    Player();
    virtual ~Player();

    void create(sf::Vector2<int> pos);

    /* Move the player */
    void move(TileMap* m);

    void warp(sf::Vector2<int> pos);

    /* Process the movement input */
    void setMovement(std::string dir);

    /* Retrieves the player sprite */
    sf::RectangleShape getSprite();

    /* Updates the logic */
    void update(TileMap* m, float t);

    sf::Vector2<int> getCurrentGridPosition();

    /* Rate at which tile takes damage */
    int damagePerTick = 5;

private:
    float speed = 3.0f;

    bool checkTileMapBounds();
    bool checkTileFloorCollision(TileMap* m);

    bool isMoving();

    /* Convert a position on the grid to a coordinate on the view */
    sf::Vector2f gridToCoord(sf::Vector2<int> pos);

    /* This is where the player currently is in the grid */
    sf::Vector2<int> currentGridPosition;

    /* This is where the player last was in the grid */
    sf::Vector2<int> previousGridPosition;

    /* This is the direction the player currently wants to move in */
    sf::Vector2<int> desiredGridMovement;

    sf::RectangleShape playerSprite;
};

#endif // PLAYER_HPP
