#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <SFML/Graphics.hpp>

class GameObject{
	public:
		void create();
		void setPosition(sf::Vector2f);
		void setPosition(float, float);

		sf::Vector2f getPosition();

	private:

		sf::Vector2f Position;

};
#endif

