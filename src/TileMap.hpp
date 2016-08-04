#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include "Tile.hpp"
#include "Player.hpp"

/* A temporary object to hold properties of different types of tiles */
/*
struct TileTypes {
    sf::Color color;
    int weight;
}, empty, dirt, snow, grass;
*/

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
    void removeTile(sf::Vector2<int> gridPoint);
    void digTile(sf::Vector2<int> gridPoint);

    /* This is a temporary function until an object is made for different types of tiles. */
    sf::Color getTileColorByType(Tile::Type);

    Tile* getTileByGridPoint(sf::Vector2<int> gridPoint);
    Tile* getTileByGridPoint(sf::Vector2<int> gridPoint, Direction dir);

    sf::VertexArray getGridLines();
    sf::VertexArray getTiles();

    static const int MAX_X = 50;
    static const int MAX_Y = 50;
private:
    bool checkInView(sf::Vector2<int> point);
    bool SHOW_GRID_LINES = true;

	TileMatrix MapData;
	//sf::VertexArray tiles;
};

#endif // TILEMAP_HPP