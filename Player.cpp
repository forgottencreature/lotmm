#include <iostream>
#include "Player.hpp"
#include "Tile.hpp"
#include "TileMap.hpp"

Player::Player()
{
	/* Create the player */
	create();
}

Player::~Player()
{

}

void Player::create()
{
	playerSprite.setPosition(Player::getCoors());
    playerSprite.setSize(sf::Vector2f(Tile::WIDTH, Tile::HEIGHT));
    playerSprite.setFillColor(sf::Color::Red);
    playerSprite.setOutlineThickness(0);
}

sf::RectangleShape Player::get()
{
	return playerSprite;
}

void Player::setSpritePosition(sf::Vector2f pos)
{
	playerSprite.setPosition(pos);
}

void Player::setGridPosition(int newGridX, int newGridY, TileMap* m)
{
    gridX = newGridX;
    gridY = newGridY;

    x = newGridX * Tile::WIDTH;
    y = newGridY * Tile::HEIGHT;

    /* Now record the previous position for future use */
    previousGridPosition = Player::getGridPosition();

    //Player::update(m);
}

void Player::move(std::string dir)
{
	
    if (Player::isMoving())
    {
        return;
    }

    previousGridPosition = Player::getGridPosition();

    if (dir == "UP")
    {
        gridY -= 1;
    }
    else if (dir == "DOWN")
    {
        gridY += 1;
    }
    if (dir == "LEFT")
    {
        gridX -= 1;
    }
    else if (dir == "RIGHT")
    {
        gridX += 1;
    }

}

void Player::update(TileMap* m, float t)
{

	/* Check boundries */
	Player::checkBounds();
	Player::checkTileCollision(m);

    /* Move right */
    if (x < gridX * Tile::WIDTH)
    {
        x = std::min(x + speed, float(gridX * Tile::WIDTH));
    }

    /* Move left */
    else if (x > gridX * Tile::WIDTH)
    {
        x = std::max(x - speed, float(gridX * Tile::WIDTH));
    }

    /* Move Down */
    if (y < gridY * Tile::WIDTH)
    {
    	//std::cout << "movign down" << "\n";
        y = std::min(y + speed, float(gridY * Tile::WIDTH));
    }

    /* Move Up */
    else if (y > gridY * Tile::WIDTH) 
    {
    	//std::cout << "movign up" << "\n";
        y = std::max(y - speed, float(gridY * Tile::WIDTH));
    }

    /* Move the sprite when it's position changes */
    playerSprite.setPosition(Player::getCoors());

}

/* Returns the physical coordinates of where the sprite currently is in the screen */
sf::Vector2f Player::getSpritePosition()
{
	return playerSprite.getPosition();
}

/* Returns the most recent X,Y coordinates of object */
sf::Vector2f Player::getCoors() 
{
    return sf::Vector2f(x,y); 
}

/* Returns where the player is on the grid */
sf::Vector2<int> Player::getGridPosition()
{
	return sf::Vector2<int>(gridX,gridY);
}

sf::Vector2<int> Player::getPreviousGridPosition()
{
	return previousGridPosition;
}

bool const Player::isMoving()
{
    return !(x == gridX * Tile::WIDTH && y == gridY * Tile::HEIGHT);
}

void Player::checkBounds() {

	/* Subtract 1 to account for the grid loop starting at 0 */
    float maxGridX = TileMap::MAX_X - 1;
    float maxGridY = TileMap::MAX_Y - 1;

    float minGridX = 0;
    float minGridY = 0;

    /* If new grid coordinates are outside of the bounds, override it and set them back. */
    gridX = (gridX < minGridX) ? minGridX : gridX;
    gridX = (gridX > maxGridX) ? maxGridX : gridX;
	gridY = (gridY < minGridY) ? minGridY : gridY;
	gridY = (gridY > maxGridY) ? maxGridY : gridY;

}

void Player::checkTileCollision(TileMap* m) {

	/* Get current Grid position */
	sf::Vector2<int> pos = Player::getGridPosition();
    sf::Vector2<int> prevPos = Player::getPreviousGridPosition();

	/* Get the corresponding tile of this position */
	Tile *t = m->getTileByGridPoint(pos);

    /* This is haxored to fuck. The tile object above should return a null pointer or something if no 
        tile is found. Instead it returns an absurdly high coordinate. So checking for that at the moment.
        THIS NEEDS TO BE FIXED!!!
    */
    if(t->getPosition().x > TileMap::MAX_X || t->getPosition().y > TileMap::MAX_Y)
    {
        //std::cout << "FOUND NULL TILE" << "\n";
    }
    else
    {
        gridX = prevPos.x;
        gridY = prevPos.y;
    }

}