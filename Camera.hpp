#include <SFML/Graphics.hpp>

namespace GAME
{

    class camera
    {
        private:
            sf::Vector2f _pos;
            sf::Vector2f _target;
            sf::Vector2f _deriv;
            sf::Vector2f _integ;
            sf::Vector2f _dist;
            sf::Vector2f _lastdist;

        public:
            void move(sf::Vector2f target);
            void setTarget(sf::Vector2f target);
            sf::Vector2f update();

    };
}
