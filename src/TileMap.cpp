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
            /* Create a tile */
            Tile t;

            /* Create a Floor */
            TileFloor tf;
            /* Create a Floor Type enum */
			TileFloor::Type chosenFloorType;

            /* Create a Block */
            TileBlock tb;
            /* Create a Block Type enum */
            TileBlock::Type chosenBlockType;

            /* For now, randomly generate block type. */
            int randNum = (rand() % 5) + 1;
            if(randNum == 1)
            {
                chosenBlockType = TileBlock::STONE;
            }
            else if(randNum == 2)
            {
                chosenBlockType = TileBlock::PEAT;
            }
            else if(randNum == 3)
            {
                chosenBlockType = TileBlock::DIRT;
            }
            else if(randNum == 4)
            {
                chosenBlockType = TileBlock::SAND;
            }
            else
            {
                chosenBlockType = TileBlock::EMPTY;
            }

            /* TILE GENERATION
             * For now I'm just creating an edge of grass and randomly populating the rest of the map
             * This should be procedurally generated at some point.
             */
            if(y == MIN_Y || x == MIN_X || y == MAX_Y-1 || x == MAX_X-1)
			{
				chosenFloorType = TileFloor::GRASS;
			}
			else
			{
				int randNum = (rand() % 3) + 1;
				if(randNum == 1)
				{
					chosenFloorType = TileFloor::GRASS;
				}
				else
				{
					chosenFloorType = TileFloor::SNOW;
				}
			}

            /* For now, override the above and set the entire map to grass */
            chosenFloorType = TileFloor::GRASS;

            /* Set the floor type */
			tf.setType(chosenFloorType);

            /* Set the block type */
            tb.setType(chosenBlockType);

            /* Update the tile properties */
			t.setFloor(tf);
            t.setBlock(tb);
            t.setPosition(x, y);

            /* Add the tile to our tile map object */
            sf::Vector2<int> v(x, y);
            MapData.insert( std::pair<sf::Vector2<int>, Tile>(v, t) );
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
sf::VertexArray TileMap::getFloor()
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

            /* For now, set the color of the tile to that of the tile's floor */
	        tile[0].color = t.getFloor().getColor();
	        tile[1].color = t.getFloor().getColor();
	        tile[2].color = t.getFloor().getColor();
	        tile[3].color = t.getFloor().getColor();
	    }
    }
    return tiles;
}

sf::VertexArray TileMap::getBlocks()
{
    sf::VertexArray floor(sf::Quads, MAX_X*MAX_Y*4);
    for (TileMatrix::const_iterator i = MapData.begin(); i != MapData.end(); ++i)
    {
        Tile t = i->second;

        sf::Vertex* tile = &floor[(t.getX() + t.getY() * MAX_X) * 4];

            // (Tile::WIDTH-TileBlock::WIDTH)/2

        tile[0].position = sf::Vector2f(t.getX() * TileBlock::WIDTH, t.getY() * TileBlock::HEIGHT);
        tile[1].position = sf::Vector2f(t.getX() * TileBlock::WIDTH + TileBlock::WIDTH, t.getY() * TileBlock::HEIGHT);
        tile[2].position = sf::Vector2f(t.getX() * TileBlock::WIDTH + TileBlock::WIDTH , t.getY() * TileBlock::HEIGHT + TileBlock::HEIGHT);
        tile[3].position = sf::Vector2f(t.getX() * TileBlock::WIDTH, t.getY() * TileBlock::HEIGHT + TileBlock::HEIGHT);

        /* For now, set the color of the tile to that of the tile's floor */
        tile[0].color = t.getBlock().getColor();
        tile[1].color = t.getBlock().getColor();
        tile[2].color = t.getBlock().getColor();
        tile[3].color = t.getBlock().getColor();
    }
    return floor;
}

void TileMap::removeFloor(sf::Vector2<int> gridPoint)
{
	Tile* t = TileMap::getTileByGridPoint(gridPoint);

	TileFloor::Type newType;
	newType = TileFloor::EMPTY;

	t->getFloor().setType(newType);
}

void TileMap::digFloor(sf::Vector2<int> gridPoint)
{
	/* Get the tile we're destroying */
	Tile* t = TileMap::getTileByGridPoint(gridPoint);
	
	if(t->getFloor().getHealth() <= 0)
	{
        TileMap::removeFloor(gridPoint);
	}
	else
	{
		t->getFloor().setHealth(t->getFloor().getHealth() - 5);

        /* Get the current color of the floor */
        sf::Color currentColor = t->getFloor().getColor();

        /* Modify the transparency to give it the effect of breaking */
		int newAlpha = (currentColor.a > 0) ? currentColor.a - Player::damagePerTick : currentColor.a;
        t->getFloor().setColor(sf::Color(currentColor.r,currentColor.g,currentColor.b,newAlpha));
	}
}

void TileMap::removeBlock(sf::Vector2<int> gridPoint)
{
    Tile* t = TileMap::getTileByGridPoint(gridPoint);

    TileBlock::Type newType;
    newType = TileBlock::EMPTY;

    t->getBlock().setType(newType);
}

void TileMap::digBlock(sf::Vector2<int> gridPoint)
{
    /* Get the tile we're destroying */
    Tile* t = TileMap::getTileByGridPoint(gridPoint);

    if(t->getFloor().getHealth() <= 0)
    {
        TileMap::removeBlock(gridPoint);
    }
    else
    {
        t->getBlock().setHealth(t->getBlock().getHealth() - 5);

        /* Get the current color of the floor */
        sf::Color currentColor = t->getBlock().getColor();

        /* Modify the transparency to give it the effect of breaking */
        int newAlpha = (currentColor.a > 0) ? currentColor.a - Player::damagePerTick : currentColor.a;
        t->getBlock().setColor(sf::Color(currentColor.r,currentColor.g,currentColor.b,newAlpha));
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