#ifndef RENDEROBJECT_HPP
#define RENDEROBJECT_HPP
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "TextureManager.hpp"

class TextureManager;

class RenderObject{
	public:
		RenderObject();
		~RenderObject();

		void setTexture(TextureManager&);
		void setPosition(sf::Vector2f);
		void setRotation(float);
		void setOrigin(int,int);

		sf::Sprite getSprite();
		sf::Vector2f getPosition();

		std::string IMGPATH;

		sf::Sprite sprite;

		float elaspedTime;

	protected:
		sf::Vector2f position;

	private:

};
#endif
