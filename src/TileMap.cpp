#include <iostream>
#include <math.h>
#include "TileMap.hpp"


TileMap::TileMap()
{
	/* 
	Pretty sure this is causing the low FPS. Don't have to draw entire tire map
	each time. Only what's in the view.
	*/
	//tiles.setPrimitiveType(sf::Quads);
	//tiles.resize(MAX_X*MAX_Y*4);
	//tiles = sf::VertexArray(sf::Quads, MAX_X*MAX_Y*4); 
}

TileMap::~TileMap()
{
	
}

void TileMap::generate()
{
    for (int x = 0; x < MAX_X; x++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
        	
            Tile t;
            Tile::Type type;
            /*
            int randNum = (rand() % 4) + 1;
            if(randNum == 1) {
            	type = Tile::snow;
            } else if(randNum == 2) {
            	type = Tile::dirt;
            } else if(randNum == 3) {
            	type = Tile::grass;
            }
			*/
			if(y == MIN_Y || x == MIN_X || y == MAX_Y-1 || x == MAX_X-1) {
				type = Tile::grass;
			} else {
				type = Tile::snow;
			}

            if (type != Tile::empty) {

                t.setType(type);
                t.setPosition(x, y);
                t.color = TileMap::getTileColorByType(type);
                sf::Vector2<int> v(x, y);
                MapData.insert( std::pair<sf::Vector2<int>, Tile>(v, t) );
            }
        }
    } 
}

sf::VertexArray TileMap::getGridLines()
{
	sf::VertexArray lines;
	lines.setPrimitiveType(sf::Lines);

	/* Only get the grid lines if they're set to be displayed */
	if(SHOW_GRID_LINES)
	{
	    for (int y = 0; y < MAX_Y + 1; y++)
        {
	    	lines.append(sf::Vertex(sf::Vector2f(0,Tile::HEIGHT*y), sf::Color(255,255,255,75)));
	    	lines.append(sf::Vertex(sf::Vector2f(Tile::WIDTH*MAX_X,Tile::HEIGHT*y), sf::Color(255,255,255,75)));
	    }
	    for (int x = 0; x < MAX_X + 1; x++)
        {
	    	lines.append(sf::Vertex(sf::Vector2f(Tile::WIDTH*x,0), sf::Color(255,255,255,75)));
	    	lines.append(sf::Vertex(sf::Vector2f(Tile::WIDTH*x,Tile::HEIGHT*MAX_Y), sf::Color(255,255,255,75)));
	    }
	}
	return lines;
}

void TileMap::toggleGrid()
{
	SHOW_GRID_LINES = !SHOW_GRID_LINES;
}

// Optimization idea - build the vertex array to the size of what is actually seen on the screen at a given time
sf::VertexArray TileMap::getTiles()
{
	// http://gamedev.stackexchange.com/questions/97881/sfml-drawing-tiles-low-fps

	sf::VertexArray tiles(sf::Quads, MAX_X*MAX_Y*4); // Pretty sure this is causing the low FPS. Do I need it in every loop iteration? 

    for (TileMatrix::const_iterator i = MapData.begin(); i != MapData.end(); ++i) {

        Tile t = i->second;

        /* Only add the tile if it's in the view - CURRENTLY EXPERIMENTAL.
        	Doesn't seem to have a beneficial effect. I think the problem is that the "tiles" vertex array is still being
        	initialized as the entire width & height of the tile map. It should only be the size of what is actually in the view.
        */
        if (TileMap::checkInView(t.getPosition()))
        {
            sf::Vertex* tile = &tiles[(t.getX() + t.getY() * MAX_X) * 4];

			tile[0].position = sf::Vector2f(t.getX() * Tile::WIDTH, t.getY() * Tile::HEIGHT);
	        tile[1].position = sf::Vector2f(t.getX() * Tile::WIDTH + Tile::WIDTH, t.getY() * Tile::HEIGHT);
	        tile[2].position = sf::Vector2f(t.getX() * Tile::WIDTH + Tile::WIDTH , t.getY() * Tile::HEIGHT + Tile::HEIGHT);
	        tile[3].position = sf::Vector2f(t.getX() * Tile::WIDTH, t.getY() * Tile::HEIGHT + Tile::HEIGHT);

	        sf::Color tileColor;
			tileColor = t.color;

	        tile[0].color = tileColor;
	        tile[1].color = tileColor;
	        tile[2].color = tileColor;
	        tile[3].color = tileColor;
	    }
    }
    return tiles;
}

/* This is a temporary function */
sf::Color TileMap::getTileColorByType(Tile::Type type)
{
	sf::Color tileColor;

    if (type == Tile::dirt) {
        return sf::Color(160,82,45);
    } else if (type == Tile::snow) {
        return sf::Color(25,25,112,255);
    } else if (type == Tile::grass) {
        return sf::Color::Green;
    } else if (type == Tile::empty) {
    	return sf::Color::Transparent;
    }

    return sf::Color::Yellow;
}

void TileMap::removeTile(sf::Vector2<int> gridPoint)
{
	MapData.erase(gridPoint);
}

void TileMap::digTile(sf::Vector2<int> gridPoint)
{
	/* Get the tile we're destorying */
	Tile* t = TileMap::getTileByGridPoint(gridPoint);
	
	if(t->health <= 0)
	{
		MapData.erase(gridPoint);
	}
	else
	{
		t->removeHealth(5);
		t->color.a = (t->color.a > 0) ? t->color.a - 5 : t->color.a;
       //std::cout << "damaging tile" << "\n";
	}
}

/* Check if a specific grid point is in the current view.
	COME BACK TO THIS
*/
bool TileMap::checkInView(sf::Vector2<int> point)
{
	return true;
}

Tile* TileMap::getTileByGridPoint(sf::Vector2<int> gridPoint)
{
    // how do I return NULL if no tile is found?!
    // also, should we be using references or pointers?
    return &MapData.find(gridPoint)->second;
}

Tile* TileMap::getTileByGridPoint(sf::Vector2<int> gridPoint, Direction dir)
{
	switch( dir )
	{
		case UP:
			return TileMap::getTileByGridPoint(sf::Vector2<int>(gridPoint.x,gridPoint.y-1));
			break;
		case DOWN:
			return TileMap::getTileByGridPoint(sf::Vector2<int>(gridPoint.x,gridPoint.y+1));
			break;
		case LEFT:
			return TileMap::getTileByGridPoint(sf::Vector2<int>(gridPoint.x+1,gridPoint.y));
			break;
		case RIGHT:
			return TileMap::getTileByGridPoint(sf::Vector2<int>(gridPoint.x-1,gridPoint.y));
			break;
		default:
			return TileMap::getTileByGridPoint(sf::Vector2<int>(gridPoint.x,gridPoint.y));
	}
}