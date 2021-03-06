#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <SFML/Graphics.hpp>

class Camera
{
	private:
		sf::Vector2f _pos;
		sf::Vector2f _target;
		sf::Vector2f _deriv;
		sf::Vector2f _integ;
		sf::Vector2f _dist;
		sf::Vector2f _lastdist;

	public:
		void move(sf::Vector2<float> target);
		void setTarget(sf::Vector2<float> target);
		sf::Vector2f update();

};

#endif // CAMERA_HPP
