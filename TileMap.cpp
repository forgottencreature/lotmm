#include <iostream>
#include <math.h>
#include "TileMap.hpp"

#define PI 3.14159265

namespace GAME
{
    TileMap::TileMap()
    {
    }
    TileMap::~TileMap()
    {

    }
    void TileMap::GenerateMap()
    {
        for (int x = 0; x < MAX_X; x++)
        {
            for (int y = 0; y < MAX_Y; y++)
            {
                Tile t;
                Tile::Material m;
                
                int randNum = (rand() % 4) + 1;
                if(randNum == 1) {
                	m = Tile::snow;
                } else if(randNum == 2) {
                	m = Tile::dirt;
                } else if(randNum == 3) {
                	m = Tile::grass;
                }

                m = Tile::grass;

                if (m != Tile::empty) {
                    t.setMaterial(m);
                    t.setPosition(x, y);
                    sf::Vector2<int> v(x, y);
                    MapData.insert( std::pair<sf::Vector2<int>, Tile>(v, t) );
                }
            }
        } 
    }

    Tile* TileMap::GetTileByGridPoint(sf::Vector2<int> gridPoint)
    {
        // how do I return NULL if no tile is found?!
        // also, should we be using references or pointers.
        //return MapData.find(gridPoint) != MapData.end();
        return &MapData.find(gridPoint)->second;
    }

    Tile* TileMap::GetTileByGridPointUp(sf::Vector2<int> gridPoint)
    {
    	return TileMap::GetTileByGridPoint(sf::Vector2<int>(gridPoint.x,gridPoint.y+1));
    }

    Tile* TileMap::GetTileByGridPointDown(sf::Vector2<int> gridPoint)
    {
    	return TileMap::GetTileByGridPoint(sf::Vector2<int>(gridPoint.x,gridPoint.y-1));
    }

    Tile* TileMap::GetTileByGridPointRight(sf::Vector2<int> gridPoint)
    {
    	return TileMap::GetTileByGridPoint(sf::Vector2<int>(gridPoint.x+1,gridPoint.y));
    }

    Tile* TileMap::GetTileByGridPointLeft(sf::Vector2<int> gridPoint)
    {
    	return TileMap::GetTileByGridPoint(sf::Vector2<int>(gridPoint.x-1,gridPoint.y));
    }

    void TileMap::RemoveTile(sf::Vector2<int> gridPoint)
    {
        MapData.erase(gridPoint);
    }

    bool TileMap::checkInView(sf::RenderWindow* tx, sf::Vector2<int> point)
    {
    	/* Grab the view from the window */
    	//sf::View view = tx->getView();
    	//sf::FloatRect viewRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
    	//bool visible = viewRect.contains(point);
    	//return visible;
    	return true;
    }

    // Optimization idea - build the vertex array to the size of what is actually seen on the screen at a given time
    void TileMap::DrawVertexArray(sf::RenderWindow* tx, float offset)
    {
    	// http://gamedev.stackexchange.com/questions/97881/sfml-drawing-tiles-low-fps
    	
    	sf::VertexArray tiles(sf::Quads, MAX_X*MAX_Y*4); // Pretty sure this is causing the low FPS. Do I need it in every loop iteration? 

        for (TileMatrix::const_iterator i = MapData.begin(); i != MapData.end(); ++i) {

            Tile t = i->second;

            /* Only add the tile if it's in the view - CURRENTLY EXPERIMENTAL.
            	Doesn't seem to have a beneficial effect. I think the problem is that the "tiles" vertex array is still being
            	initialized as the entire width & height of the tile map. It should only be the size of what is actually in the view.
            */
            if (TileMap::checkInView(tx, t.getPosition()))
            {

	            sf::Vertex* tile = &tiles[(t.getX() + t.getY() * MAX_X) * 4];

				tile[0].position = sf::Vector2f(t.getX() * Tile::WIDTH, t.getY() * Tile::HEIGHT);
		        tile[1].position = sf::Vector2f(t.getX() * Tile::WIDTH + Tile::WIDTH, t.getY() * Tile::HEIGHT);
		        tile[2].position = sf::Vector2f(t.getX() * Tile::WIDTH + Tile::WIDTH , t.getY() * Tile::HEIGHT + Tile::HEIGHT);
		        tile[3].position = sf::Vector2f(t.getX() * Tile::WIDTH, t.getY() * Tile::HEIGHT + Tile::HEIGHT);

		        sf::Color tileColor;
		        if (t.getMaterial() == Tile::dirt) {
		            tileColor = sf::Color(160,82,45);
		        } else if (t.getMaterial() == Tile::snow) {
		            tileColor = sf::Color(25,25,112);
		        } else if (t.getMaterial() == Tile::grass) {
		            tileColor = sf::Color::Green;
		        } else if (t.getMaterial() == Tile::empty) {
		            //tileColor = sf::Color::Black;
		            //std::cout << " FOUND EMPTY TILE " << "\n";
		        }

		        tile[0].color = tileColor;
		        tile[1].color = tileColor;
		        tile[2].color = tileColor;
		        tile[3].color = tileColor;

		    }

        }

        tx->draw(tiles);
    }

    void TileMap::DrawTileGrid(sf::RenderWindow* tx, float offset)
    {
    	if(SHOW_GRID_LINES == true)
    	{
			sf::VertexArray lines;
		    lines.setPrimitiveType(sf::Lines);

		    for (int y = 0; y < MAX_Y + 1; y++)
	        {
		    	lines.append(sf::Vertex(sf::Vector2f(0,GAME::Tile::HEIGHT*y), sf::Color::Black));
		    	lines.append(sf::Vertex(sf::Vector2f(GAME::Tile::WIDTH*MAX_X,GAME::Tile::HEIGHT*y), sf::Color::White));
		    }
		    for (int x = 0; x < MAX_X + 1; x++)
	        {
		    	lines.append(sf::Vertex(sf::Vector2f(GAME::Tile::WIDTH*x,0), sf::Color::Black));
		    	lines.append(sf::Vertex(sf::Vector2f(GAME::Tile::WIDTH*x,GAME::Tile::HEIGHT*MAX_Y), sf::Color::White));
		    }

		    tx->draw(lines);
		}
    }

    void TileMap::ToggleGrid()
    {
    	SHOW_GRID_LINES = !SHOW_GRID_LINES;
    }
}
