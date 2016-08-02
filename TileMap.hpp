#ifndef _tilemap_h_ 
#define _tilemap_h_
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

namespace GAME
{
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
            void GenerateMap();
            void DrawVertexArray(sf::RenderWindow* tx, float offset);
            void DrawTileGrid(sf::RenderWindow* tx, float offset);
            void RemoveTile(sf::Vector2<int> gridPoint);
            void ToggleGrid();

            // merge these functions into 1
            Tile GetTileByGridPoint(sf::Vector2<int> gridPoint);
            Tile GetTileByGridPointUp(sf::Vector2<int> gridPoint);
            Tile GetTileByGridPointDown(sf::Vector2<int> gridPoint);
            Tile GetTileByGridPointLeft(sf::Vector2<int> gridPoint);
            Tile GetTileByGridPointRight(sf::Vector2<int> gridPoint);

            bool checkInView(sf::RenderWindow* tx, sf::Vector2<int> point);
            bool SHOW_GRID_LINES = true;
            static const int MAX_X = 360;
            static const int MAX_Y = 72;
        protected:
        private:
            TileMatrix MapData;
    };
}

#endif