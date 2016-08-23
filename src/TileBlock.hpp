#ifndef TILEBLOCK_HPP
#define TILEBLOCK_HPP

#include <SFML/Graphics.hpp>

class TileBlock{
	public:
		enum Type { EMPTY, STONE, PEAT, DIRT, SAND, TEST };

		TileBlock();
		virtual ~TileBlock();

		void setType(Type t);
		void setColor(sf::Color c);
		sf::Color getColor();

		void setHealth(int h);
		int getHealth();
		float getHardness();

		bool canPassThrough();

		static const int HEIGHT = 24;
		static const int WIDTH = 24;

		/* This isn't working
			 static const int HEIGHT = Tile::HEIGHT - 10;
			 static const int WIDTH = Tile::WIDTH - 10;
			 */

	private:
		sf::Color color;
		int health;
		float hardness;
		bool passThrough;
};

#endif // TILEBLOCK_HPP
