#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"

TextureManager::TextureManager() : textures_(), resource_directories_(){
}

TextureManager::~TextureManager(){
	textures_.clear();
	resource_directories_.clear();
}

const sf::Texture& TextureManager::get_texture( const std::string& filename ){
	// Check, whether the texture already exists
	for( std::map<std::string, sf::Texture>::const_iterator it = textures_.begin(); it != textures_.end(); ++it){
		if( filename == it->first ){
			std::cout << "DEBUG_MESSAGE: " << filename << " using existing texture.\n";
			return it->second;
		}
	}

	// The texture doesen't exists. Create it and save it.
	sf::Texture texture;
	texture.setSmooth(true);

	// Search project's main directory
	if( texture.loadFromFile( filename ) ){
		textures_[filename] = texture;
		std::cout << "DEBUG_MESSAGE: " << filename << " loading texture.\n";
		return textures_[filename];
	}

	// If the texture has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = resource_directories_.begin(); it != resource_directories_.end(); ++it ){
		if( texture.loadFromFile( (*it) + filename ) ){
			textures_[filename] = texture;
			std::cout << "DEBUG_MESSAGE: " << filename << " loading texture.\n";
			return textures_[filename];
		}
	}

	std::cout << "GAME_ERROR: texture was not found. It is filled with an empty texture.\n";
	textures_[filename] = texture;
	return textures_[filename];
}

//ytf dont this work
/*void TextureManager::delete_texture( const sf::Texture& texture )
	{
	for( std::map<std::string, sf::Texture>::const_iterator it = textures_.begin();
	it != textures_.end();
	++it)
	{
	if( &texture == &it->second )
	{
	textures_.erase( it );
	return;
	}
	}
	}*/

void TextureManager::delete_texture( const std::string& filename ){
	std::map<std::string, sf::Texture>::const_iterator it = textures_.find( filename );
	if( it != textures_.end() )
	{
		//textures_.erase( it );      //ytf dont this work?
		textures_.erase( textures_.find( filename ) );
	}
}

void TextureManager::add_resource_directory( const std::string& directory ){
	// Check whether the path already exists
	for( std::vector<std::string>::const_iterator it  = resource_directories_.begin(); it != resource_directories_.end(); ++it ){
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			return;
	}

	// insert the directory
	resource_directories_.push_back( directory );
}

void TextureManager::remove_resource_directory( const std::string& directory ){
	for( std::vector<std::string>::iterator it  = resource_directories_.begin(); it != resource_directories_.end(); ){
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			it = resource_directories_.erase( it );
		else
			++it;
	}
}
