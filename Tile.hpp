#ifndef _tile_h_ 
#define _tile_h_
#include <SFML/Graphics.hpp>

namespace GAME
{
    class Tile
    {
        public:
            enum Material
            {
                empty,
                dirt,
                snow,
                grass,
            };
            Tile();
            virtual ~Tile();
            void setPosition(sf::Vector2<int> p);
            void setPosition(int x, int y);
            void setMaterial(Material m);
            sf::Vector2<int> getPosition();
            int getX();
            int getY();
            Material getMaterial();
            static const int HEIGHT = 8;
            static const int WIDTH = 8;
        protected:
        private:
            Material material;
            sf::Vector2<int> position;
    };

    sf::Color hsv(int hue, float sat, float val);
}

#endif