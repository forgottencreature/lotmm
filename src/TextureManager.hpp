#ifndef TextureManager_H_
#define TextureManager_H_

#include <map>
#include <iostream>

class TextureManager
{
	public:
		TextureManager();
		~TextureManager();

	private:
		TextureManager( const TextureManager& );
		TextureManager& operator =( const TextureManager& );

	public:
		const sf::Texture&	get_texture( const std::string& filename );
		void	delete_texture( const sf::Texture& texture );
		void	delete_texture( const std::string& filename );
		void	add_resource_directory( const std::string& directory );
		void	remove_resource_directory( const std::string& directory );

	private:
		std::map< std::string, sf::Texture > textures_;
		std::vector< std::string > resource_directories_;
};
#endif
