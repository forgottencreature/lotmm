#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include "Tile.hpp"
#include "Player.hpp"
#include <Thor/Particles.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Math/Distributions.hpp>

class Player;

struct classcomp {
	bool operator() (const sf::Vector2<int>& a, const sf::Vector2<int>& b) const
	{
		return a.x < b.x || (a.x == b.x && a.y < b.y);
	}
};

typedef std::map<sf::Vector2<int>, Tile, classcomp> TileMatrix;

class TileMap 
{
	public:
		TileMap();
		virtual ~TileMap();

		enum Direction { UP, DOWN, LEFT, RIGHT };

		void generate();
		void toggleGrid();

		void removeFloor(sf::Vector2<int> gridPoint);
		void digFloor(sf::Vector2<int> gridPoint, int damagePerTick);

        thor::UniversalEmitter* removeBlock(sf::Vector2<int> gridPoint);
        thor::UniversalEmitter* digBlock(sf::Vector2<int> gridPoint, int damagePerTick);

		Tile* getTileByGridPoint(sf::Vector2<int> gridPoint);
		Tile* getTileByGridPoint(sf::Vector2<int> gridPoint, Direction dir);

		sf::VertexArray getGridLines();
		sf::VertexArray getFloor();
		sf::VertexArray getBlocks();

		int blockAnimCount=2;

		static const int MAX_X = 360;
		static const int MAX_Y = 100;
		static const int MIN_X = 0;
		static const int MIN_Y = 0;

	private:
		bool checkInView(sf::Vector2<int> point);
		bool SHOW_GRID_LINES = false;

		TileMatrix MapData;
		//sf::VertexArray tiles;
};

#endif // TILEMAP_HPP
