#include <iostream>
#include "Player.hpp"
#include "Tile.hpp"
#include "TileMap.hpp"

Player::Player()
{

}

Player::~Player()
{

}

void Player::create(sf::Vector2<int> pos)
{
	playerSprite.setPosition(Player::gridToCoord(pos));
    playerSprite.setSize(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
    playerSprite.setFillColor(sf::Color::Red);
    playerSprite.setOutlineThickness(0);

    /* Set the current position */
    currentGridPosition = pos;

    /* When we start out, populate previous position with where they start so that it isn't moving */
    previousGridPosition = pos;
}

sf::RectangleShape Player::getSprite()
{
    return playerSprite;
}

void Player::update()
{
    sf::Vector2<int> newPos = previousGridPosition + desiredGridMovement;

    /* Update the player sprite to the correct position */
    playerSprite.setPosition(Player::gridToCoord(previousGridPosition + desiredGridMovement));

    /* If the player has reached it's destination, update the current position. */
    if(!Player::isMoving())
    {
        currentGridPosition = newPos;
        //std::cout << "DESTINATION REACHED!!" << "\n";
    }

}

void Player::move(std::string dir)
{

    /* Check if the player is already moving */
    if (Player::isMoving())
    {
        return;
    }

    /* Check if the player is trying to move outside the grid*/
    if(Player::checkTileMapBounds())
    {
        std::cout << "COLLISION WARNING! Tile map bounds." << "\n";
        return;
    }

    /* Check if the player is trying to move onto occupied tile */
    if(Player::checkTileCollision())
    {
        std::cout << "COLLISION WARNING! Occupied tile." << "\n";
        return;
    }

    /* Update the previous grid position to what the player is currently at */
    previousGridPosition = Player::currentGridPosition;

    if (dir == "UP")
    {
        desiredGridMovement = sf::Vector2<int>(0,-1);
    }
    else if (dir == "DOWN")
    {
        desiredGridMovement = sf::Vector2<int>(0,1);
    }
    if (dir == "LEFT")
    {
        desiredGridMovement = sf::Vector2<int>(-1,0);
    }
    else if (dir == "RIGHT")
    {
        desiredGridMovement = sf::Vector2<int>(1,0);
    }

}

sf::Vector2f Player::gridToCoord(sf::Vector2<int> pos)
{
    return sf::Vector2f((pos.x-1)*Tile::WIDTH,(pos.y-1)*Tile::HEIGHT);
}

bool Player::checkTileMapBounds()
{
    int minGridX = TileMap::MIN_X + 1;
    int minGridY = TileMap::MIN_Y + 1;

    /* Subtract 1 to account for the grid loop starting at 0 */
    int maxGridX = TileMap::MAX_X ;
    int maxGridY = TileMap::MAX_Y;

    /* Figure out where the player wants to be, given the provided input */
    sf::Vector2<int> desiredGridPosition = previousGridPosition + desiredGridMovement;

    /* Check if the desired position is outside the bounds */
    bool collision = desiredGridPosition.x > maxGridX || desiredGridPosition.x < minGridX || desiredGridPosition.y > maxGridY || desiredGridPosition.y < minGridY;

    /* If there is collision, we need to void out the desired movement. */
    if(collision)
    {
        desiredGridMovement = sf::Vector2<int>(0, 0);
    }

    return collision;

}

bool Player::checkTileCollision()
{
    return false;
}

bool Player::isMoving()
{
    return Player::gridToCoord(previousGridPosition + desiredGridMovement) != playerSprite.getPosition();
}