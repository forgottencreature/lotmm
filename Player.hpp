#ifndef _player_h_ 
#define _player_h_
#include <SFML/Graphics.hpp>

namespace GAME
{

    class TileMap;

    struct Dir {
        enum Type {Up, Right, Down, Left, None};
    };

    class Player
    {
        public:
            Player();
            virtual ~Player();
            void setPosition(int newGridX, int newGridY, GAME::TileMap* m);
            void move(const GAME::Dir::Type dir);
            void draw(sf::RenderWindow* tx);
            void const update(GAME::TileMap* m);
            sf::Vector2f getSpritePosition();
            sf::Vector2<int> getGridPosition();
            sf::Vector2<int> getPreviousGridPosition();
        protected:
        private:
            float x, y;
            float speed = 1.0f;
            int gridX, gridY;
            void create();
            void setSpritePosition(sf::Vector2f pos);
            void checkBounds();
            void checkTileCollision(TileMap* m);
            bool const isMoving();
            sf::Vector2f getCoors();
            sf::RectangleShape playerSprite;
            sf::Vector2<int> previousGridPosition;
    };

}

#endif