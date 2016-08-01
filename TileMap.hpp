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
            static const int MAX_X = 360;
            static const int MAX_Y = 72;
        protected:
        private:
            TileMatrix MapData;
    };
}
