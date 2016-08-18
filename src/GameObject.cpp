//Gameobjects include walls, renderobjects, etc
#include "GameObject.hpp"

void GameObject::create() {

}

void GameObject::setPosition(sf::Vector2f pos) {
	GameObject::Position = pos;
}

void GameObject::setPosition(float x, float y) {
	GameObject::Position = sf::Vector2f(x,y);
}

sf::Vector2f GameObject::getPosition() {
	return Position;
}


