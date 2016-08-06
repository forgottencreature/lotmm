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

void Player::update(TileMap* m, float t)
{
    Player::move(m);
}

void Player::move(TileMap* m)
{
    /* Check if the player is trying to move outside the grid*/
    if(Player::checkTileMapBounds())
    {
        //std::cout << "COLLISION WARNING! Tile map bounds." << "\n";
        return;
    }

    /* Check if the player is trying to move onto tile with floor that has collision */
    if(!Player::checkTileFloorCollision(m))
    {
        return;
    }

    sf::Vector2<int> newPos = previousGridPosition + desiredGridMovement;

    /* Update the player sprite to the correct position */
    playerSprite.setPosition(Player::gridToCoord(previousGridPosition + desiredGridMovement));

    /* If the player has reached it's destination, update the current position. */
    if(!Player::isMoving())
    {
        currentGridPosition = newPos;
    }
}

void Player::setMovement(std::string dir)
{

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
    return sf::Vector2f((pos.x)*Tile::WIDTH,(pos.y)*Tile::HEIGHT);
}

bool Player::checkTileMapBounds()
{
    int minGridX = TileMap::MIN_X;
    int minGridY = TileMap::MIN_Y;

    /* Subtract 1 to account for the grid loop starting at 0 */
    int maxGridX = TileMap::MAX_X - 1;
    int maxGridY = TileMap::MAX_Y - 1;

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

bool Player::checkTileFloorCollision(TileMap* m)
{
    /* Figure out where the player wants to be, given the provided input */
    sf::Vector2<int> desiredGridPosition = previousGridPosition + desiredGridMovement;

    /* Get the corresponding tile of this position */
    Tile *t = m->getTileByGridPoint(desiredGridPosition);

    return t->getFloor().canPassThrough();
}

bool Player::isMoving()
{
    return Player::gridToCoord(previousGridPosition + desiredGridMovement) != playerSprite.getPosition();
}