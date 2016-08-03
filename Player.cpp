#include <iostream>
#include "Player.hpp"
#include "TileMap.hpp"
#include "Camera.hpp"

namespace GAME
{
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
	    playerSprite.setSize(sf::Vector2f(GAME::Tile::WIDTH, GAME::Tile::HEIGHT));
	    playerSprite.setFillColor(sf::Color::Red);
	    playerSprite.setOutlineThickness(0);
    }

    void Player::draw(sf::RenderWindow* tx)
    {
    	tx->draw(playerSprite);
    }

    sf::Vector2f Player::getSpritePosition()
    {
    	return playerSprite.getPosition();
    }

    sf::Vector2<int> Player::getGridPosition()
    {
    	return sf::Vector2<int>(gridX,gridY);
    }

    sf::Vector2<int> Player::getPreviousGridPosition()
    {
    	return previousGridPosition;
    }

    void Player::setSpritePosition(sf::Vector2f pos)
    {
		playerSprite.setPosition(pos);
    }

    bool const Player::isMoving()
    {
        return !(x == gridX * GAME::Tile::WIDTH && y == gridY * GAME::Tile::HEIGHT);
    }

    void Player::setPosition(int newGridX, int newGridY, GAME::TileMap* m)
    {
        gridX = newGridX;
        gridY = newGridY;

        x = newGridX * GAME::Tile::WIDTH;
        y = newGridY * GAME::Tile::WIDTH;

        previousGridPosition = Player::getGridPosition();

        Player::update(m);
    }

    void Player::move(const Dir::Type dir)
    {
        if (Player::isMoving())
        {
            return;
        }
 
        previousGridPosition = Player::getGridPosition();

        if (dir == GAME::Dir::Up)
        {
            gridY -= 1;
        }
        else if (dir == GAME::Dir::Down)
        {
            gridY += 1;
        }
        if (dir == GAME::Dir::Left)
        {
            gridX -= 1;
        }
        else if (dir == GAME::Dir::Right)
        {
            gridX += 1;
        }
    }

    void const Player::update(TileMap* m)
    {

    	/* Check boundries */
		Player::checkBounds();
		Player::checkTileCollision(m);


        /* Move right */
        if (x < gridX * GAME::Tile::WIDTH)
        {
            x = std::min(x + speed, float(gridX * GAME::Tile::WIDTH));
        }

        /* Move left */
        else if (x > gridX * GAME::Tile::WIDTH)
        {
            x = std::max(x - speed, float(gridX * GAME::Tile::WIDTH));
        }

        /* Move Down */
        if (y < gridY * GAME::Tile::WIDTH)
        {
            y = std::min(y + speed, float(gridY * GAME::Tile::WIDTH));
        }

        /* Move Up */
        else if (y > gridY * GAME::Tile::WIDTH) 
        {
            y = std::max(y - speed, float(gridY * GAME::Tile::WIDTH));
        }

        /* Move the sprite when it's position changes */
        playerSprite.setPosition(Player::getCoors());
    }

	void Player::checkBounds() {

		/* Subtract 1 to account for the grid loop starting at 0 */
	    float maxGridX = GAME::TileMap::MAX_X - 1;
	    float maxGridY = GAME::TileMap::MAX_Y - 1;

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
		Tile *t = m->GetTileByGridPoint(pos);

        /* This is haxored to fuck. The tile object above should return a null pointer or something if no 
            tile is found. Instead it returns an absurdly high coordinate. So checking for that at the moment.
            THIS NEEDS TO BE FIXED!!!
        */
        if(t->getPosition().x > GAME::TileMap::MAX_X || t->getPosition().y > GAME::TileMap::MAX_Y)
        {
            //std::cout << "FOUND NULL TILE" << "\n";
        }
        else
        {
            gridX = prevPos.x;
            gridY = prevPos.y;
            //std::cout << "COLLISION: BRINGING TO PREVIOUS POSITION: " << "\n";
            //std::cout << prevPos.x << " " << prevPos.y << "\n";
	    }
	}

    sf::Vector2f Player::getCoors() 
    {
        return sf::Vector2f(x,y); 
    }


}