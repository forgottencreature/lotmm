#include "RenderObject.hpp"
#include "TextureManager.hpp"

RenderObject::RenderObject(){

}

RenderObject::~RenderObject(){

}

void RenderObject::setTexture(TextureManager& textureManager){
	RenderObject::sprite.setTexture(textureManager.get_texture(RenderObject::IMGPATH));
	//std::cout << "texture set " << RenderObject::IMGPATH << std::endl;
}

sf::Sprite RenderObject::getSprite(){
	return RenderObject::sprite;
}

sf::Vector2f RenderObject::getPosition(){
	return RenderObject::position;
}

void RenderObject::setPosition(sf::Vector2f pos){
	RenderObject::position = pos;
	RenderObject::sprite.setPosition(pos);
}

void RenderObject::setOrigin(int x,int y){
	RenderObject::sprite.setOrigin(x,y);
}

void RenderObject::setRotation(float rot){
	sprite.setRotation(180/3.1f * rot);
}

