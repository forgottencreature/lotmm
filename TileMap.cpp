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
                
                int randNum = (rand() % 3) + 1;
                if(randNum == 1) {
                	m = Tile::snow;
                } else if(randNum == 2) {
                	m = Tile::dirt;
                } else if(randNum == 3) {
                	m = Tile::grass;
                }
				
                // this generated snow capped mountains
                /*
                if (x % 180 == 68 && y == 27) {
                    m = Tile::empty;
                } else if (7*sin(12*x*PI/180) + 3*sin(6*x*PI/180) + -2*cos(2*x*PI/180) > y - 13) {
                    if (y > 15 && 7*sin(12*x*PI/180) + 3*sin(6*x*PI/180) + -2*cos(2*x*PI/180) < y - 10) {
                        m = Tile::snow;
                    } else if (7*sin(12*x*PI/180) + 3*sin(6*x*PI/180) + -2*cos(2*x*PI/180) > y - 11) {
                        m = Tile::dirt;
                    } else {
                        m = Tile::grass;
                    }
                } else {
                    m = Tile::empty;
                }
				*/

                //m = Tile::snow;

                if (m != Tile::empty) {
                    t.setMaterial(m);
                    t.setPosition(x, y);
                    sf::Vector2<int> v(x, y);
                    MapData.insert( std::pair<sf::Vector2<int>, Tile>(v, t) );
                }
            }
        }
    }

    void TileMap::DrawVertexArray(sf::RenderWindow* tx, float offset)
    {
    	// http://gamedev.stackexchange.com/questions/97881/sfml-drawing-tiles-low-fps
    	
    	sf::VertexArray tiles(sf::Quads, MAX_X*MAX_Y*4);

        for (TileMatrix::const_iterator i = MapData.begin(); i != MapData.end(); ++i) {

            Tile t = i->second;

            sf::Vertex* tile = &tiles[(t.getX() + t.getY() * MAX_X) * 4];

			tile[0].position = sf::Vector2f(t.getX() * Tile::WIDTH, t.getY() * Tile::HEIGHT);
	        tile[1].position = sf::Vector2f(t.getX() * Tile::WIDTH + Tile::WIDTH, t.getY() * Tile::HEIGHT);
	        tile[2].position = sf::Vector2f(t.getX() * Tile::WIDTH + Tile::WIDTH , t.getY() * Tile::HEIGHT + Tile::HEIGHT);
	        tile[3].position = sf::Vector2f(t.getX() * Tile::WIDTH, t.getY() * Tile::HEIGHT + Tile::HEIGHT);

	        sf::Color tileColor;
	        if (t.getMaterial() == Tile::dirt) {
	            tileColor = sf::Color(160,82,45);
	        } else if (t.getMaterial() == Tile::snow) {
	            //tileColor = sf::Color::White;
	            //tileColor = sf::Color(105,105,105);
	            tileColor = sf::Color(25,25,112);
	        } else if (t.getMaterial() == Tile::grass) {
	            tileColor = sf::Color::Green;
	        }

	        tile[0].color = tileColor;
	        tile[1].color = tileColor;
	        tile[2].color = tileColor;
	        tile[3].color = tileColor;

            //t.DrawVertexArray(tx, offset);
        }

        tx->draw(tiles);
    }

    void TileMap::DrawTileGrid(sf::RenderWindow* tx, float offset)
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
