#include <SFML/Graphics.hpp>

namespace GAME
{

    struct Dir {
        enum Type {Up, Right, Down, Left};
    };

    class Player
    {
        public:
            float x, y;
            float speed = 4.0f;
            int gridX, gridY;
            sf::RectangleShape playerSprite;
            Player();
            virtual ~Player();
            void warp(int newGridX, int newGridY);
            void move(const GAME::Dir::Type dir);
            void draw(sf::RenderWindow* tx);
            void const update();
            bool const isMoving();
            sf::Vector2f getCoors();
            sf::Vector2f getSpritePosition();
            void setSpritePosition(sf::Vector2f pos);
        protected:
        private:
    };

}
