#include <iostream>
#include <math.h>
#include "Tile.hpp"

Tile::Tile(){

}

Tile::~Tile(){

}

void Tile::setPosition(sf::Vector2<int> p){
	Tile::position = p;
}

void Tile::setPosition(int x, int y){
	Tile::position = sf::Vector2<int>(x, y);
}


void Tile::setFloor(TileFloor f){
	Tile::floor = f;
}

void Tile::setBlock(TileBlock b){
	Tile::block = b;
}

/*
void Tile::removeHealth(int i) 
{
	Tile::floor.health = Tile::floor.health - i;
}
*/

TileFloor& Tile::getFloor(){
	return Tile::floor;
}

TileBlock& Tile::getBlock(){
	return Tile::block;
}

sf::Vector2<int> Tile::getPosition(){
	return Tile::position;
}

int Tile::getX(){
	return Tile::position.x;
}

int Tile::getY(){
	return Tile::position.y;
}
