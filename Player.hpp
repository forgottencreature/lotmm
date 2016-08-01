#include <SFML/Graphics.hpp>

namespace GAME
{

    struct Dir {
        enum Type {Up, Right, Down, Left};
    };

    class Player
    {
        public:
            Player();
            virtual ~Player();
            void warp(int newGridX, int newGridY);
            void move(const GAME::Dir::Type dir);
            void draw(sf::RenderWindow* tx);
            void const update();
            sf::Vector2f getSpritePosition();
        protected:
        private:
            float x, y;
            float speed = 4.0f;
            int gridX, gridY;
            void create();
            void setSpritePosition(sf::Vector2f pos);
            bool const isMoving();
            sf::Vector2f getCoors();
            sf::RectangleShape playerSprite;
    };

}
