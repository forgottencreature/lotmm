#include <iostream>
#include "Player.hpp"
#include "Tile.hpp"
#include "TileMap.hpp"

Player::Player(){

}

Player::~Player(){

}

void Player::create(sf::Vector2<int> pos){
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

sf::Vector2<int> Player::getDesiredMovement(){
	return desiredGridMovement;
}

void Player::update(TileMap* m, float dt){

	//If movement accumulator(frames) is greater than our period, move.
	if(movementAccumulator >= movementPeriod){ 
		move(m);
	}
	movementAccumulator+=1;
}

void Player::move(TileMap* m){
	//Check where character is going to move, if valid allow.
	//Was a direction pressed for which way to go?
	if(desiredGridMovement != sf::Vector2<int>(0,0)){
		//Is the desired direction now that it isn't 0,0 in the map?
		if(checkTileMapBounds()){
	//std::cout << movementAccumulator << std::endl;
			//Is the desired movement a passable block?
			if(checkTileFloorCollision(m)){
				previousGridPosition=currentGridPosition;
				currentGridPosition+=desiredGridMovement;
				desiredGridMovement=sf::Vector2<int>(0,0);
				//Set the move accumulator now so that we don't lose movement when not moving
				movementAccumulator=-1;
			}
		}
	}
	//Change sprite position accordingly for now, it will be jumpy till animation is added for the sprite
	playerSprite.setPosition(gridToCoord(currentGridPosition));
}

/* void Player::update(TileMap* m, float t){ */
/* 	Player::move(m); */
/* } */

/* void Player::move(TileMap* m){ */
/* 	Check if the player is trying to move outside the grid*/
/* 	if(Player::checkTileMapBounds()){ */
/* 		return; */
/* 	} */

/* 	/1* Check if the player is trying to move onto tile with floor that has collision *1/ */
/* 	if(!Player::checkTileFloorCollision(m)){ */
/* 		return; */
/* 	} */

/* 	sf::Vector2<int> newPos = previousGridPosition + desiredGridMovement; */

/* 	/1* Update the player sprite to the correct position *1/ */

/* 	//playerSprite.setPosition(playerSprite.getPosition()+sf::Vector2<float>(desiredGridMovement.x * Player::speed,desiredGridMovement.y * Player::speed)); */

/* 	playerSprite.setPosition(Player::gridToCoord(previousGridPosition + desiredGridMovement)); */

/* 	/1* If the player has reached it's destination, update the current position. *1/ */
/* 	if(!Player::isMoving()){ */
/* 		currentGridPosition = newPos; */
/* 	} */
/* } */

void Player::warp(sf::Vector2<int> pos) {
	playerSprite.setPosition(Player::gridToCoord(pos));
	currentGridPosition = pos;
	previousGridPosition = pos;
}

void Player::setMovement(std::string dir){

	/* Update the previous grid position to what the player is currently at */
	previousGridPosition = Player::currentGridPosition;

	if (dir == "UP"){
		desiredGridMovement = sf::Vector2<int>(0,-1);
	}
	else if (dir == "DOWN"){
		desiredGridMovement = sf::Vector2<int>(0,1);
	}
	if (dir == "LEFT"){
		desiredGridMovement = sf::Vector2<int>(-1,0);
	}
	else if (dir == "RIGHT"){
		desiredGridMovement = sf::Vector2<int>(1,0);
	}
	if (dir == "NEUTRAL"){
		desiredGridMovement = sf::Vector2<int>(0,0);
	}

}

sf::Vector2f Player::gridToCoord(sf::Vector2<int> pos){
	return sf::Vector2f((pos.x)*Tile::WIDTH,(pos.y)*Tile::HEIGHT);
}

sf::Vector2<int> Player::getCurrentGridPosition(){
	return currentGridPosition;
}

bool Player::checkTileMapBounds(){
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
	if(collision){
		desiredGridMovement = sf::Vector2<int>(0, 0);
	}

	return !collision;

}

bool Player::checkTileFloorCollision(TileMap* m){
	/* Figure out where the player wants to be, given the provided input */
	sf::Vector2<int> desiredGridPosition = currentGridPosition + desiredGridMovement;

	/* Get the corresponding tile of this position */
	Tile *t = m->getTileByGridPoint(desiredGridPosition);

	return t->getBlock().canPassThrough();
}

bool Player::isMoving(){
	return Player::gridToCoord(previousGridPosition + desiredGridMovement) != playerSprite.getPosition();
}
