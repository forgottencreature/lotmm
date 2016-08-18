#include <iostream>
#include "TileFloor.hpp"

TileFloor::TileFloor(){

}

TileFloor::~TileFloor(){

}

void TileFloor::setType(Type t){
	switch(t){
		case EMPTY:
			this->color = sf::Color::Transparent;
			this->health = 0;
			this->passThrough = true;
			break;
		case DIRT:
			this->color = sf::Color(30,30,30);
			this->health = 100;
			this->passThrough = false;
			break;
		case SNOW:
			this->color = sf::Color(40,40,40);
			this->health = 100;
			this->passThrough = false;
			break;
		case GRASS:
			this->color = sf::Color(50,50,50);
			this->health = 100;
			this->passThrough = true;
			break;
		default:
			this->color = sf::Color::Transparent;
			this->health = 0;
			this->passThrough = true;
	}
}

void TileFloor::setColor(sf::Color c){
	this->color = c;
}

sf::Color TileFloor::getColor(){
	return this->color;
}

void TileFloor::setHealth(int h){
	this->health = h;
}

int TileFloor::getHealth(){
	return this->health;
}

bool TileFloor::canPassThrough(){
	return this->passThrough;
}
