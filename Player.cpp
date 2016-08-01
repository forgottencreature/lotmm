#include <iostream>
#include "Player.hpp"
#include "Tile.hpp"
#include "Camera.hpp" 

namespace GAME
{
    Player::Player()
    {
    	/* Create the player */
    	//sf::RectangleShape playerSprite;

    	playerSprite.setPosition(Player::getCoors());
	    playerSprite.setSize(sf::Vector2f(GAME::Tile::WIDTH, GAME::Tile::HEIGHT));
	    playerSprite.setFillColor(sf::Color::Red);
	    playerSprite.setOutlineThickness(0);
    }

    Player::~Player()
    {

    }

    void Player::draw(sf::RenderWindow* tx)
    {
    	tx->draw(playerSprite);
    }

    sf::Vector2f Player::getSpritePosition()
    {
    	return playerSprite.getPosition();
    }

    void Player::setSpritePosition(sf::Vector2f pos)
    {
		playerSprite.setPosition(pos);
    }

    bool const Player::isMoving()
    {
        return !(x == gridX * GAME::Tile::WIDTH && y == gridY * GAME::Tile::HEIGHT);
    }

    void Player::warp(int newGridX, int newGridY)
    {
        gridX = newGridX;
        gridY = newGridY;

        x = newGridX * GAME::Tile::WIDTH;
        y = newGridY * GAME::Tile::WIDTH;
    }

    void Player::move(const Dir::Type dir)
    {
        if (Player::isMoving())
        {
            return;
        }

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

    void const Player::update()
    {
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

    sf::Vector2f Player::getCoors() 
    {
        return sf::Vector2f(x,y); 
    }


}