#include <iostream>
#include <math.h>
#include "Tile.hpp"

namespace GAME
{
    Tile::Tile()
    {

    }

    Tile::~Tile()
    {

    }

    void Tile::setPosition(sf::Vector2<int> p) {
        Tile::position = p;
    }

    void Tile::setPosition(int x, int y) {
        Tile::position = sf::Vector2<int>(x, y);
    }

    void Tile::setMaterial(Material m) {
        Tile::material = m;
    }

    sf::Vector2<int> Tile::getPosition() {
        return Tile::position;
    }

    int Tile::getX() {
        return Tile::position.x;
    }

    int Tile::getY() {
        return Tile::position.y;
    }

    Tile::Material Tile::getMaterial() {
        return Tile::material;
    }

    void Tile::DrawVertexArray(sf::RenderWindow* tx, float offset) {
/*
        int a = ceil(offset / 1800);

        // create a quad
        sf::VertexArray tile(sf::Quads, 4);


//        tile[0].position = sf::Vector2f(Tile::getX() * Tile::WIDTH -offset+a*1800-900, Tile::getY() * Tile::HEIGHT);
//       tile[1].position = sf::Vector2f(Tile::getX() * Tile::WIDTH + Tile::WIDTH -offset+a*1800-900, Tile::getY() * Tile::HEIGHT);
//        tile[2].position = sf::Vector2f(Tile::getX() * Tile::WIDTH + Tile::WIDTH -offset+a*1800-900, Tile::getY() * Tile::HEIGHT + Tile::HEIGHT);
//        tile[3].position = sf::Vector2f(Tile::getX() * Tile::WIDTH -offset+a*1800-900, Tile::getY() * Tile::HEIGHT + Tile::HEIGHT);


        tile[0].position = sf::Vector2f(Tile::getX() * Tile::WIDTH, Tile::getY() * Tile::HEIGHT);
        tile[1].position = sf::Vector2f(Tile::getX() * Tile::WIDTH + Tile::WIDTH, Tile::getY() * Tile::HEIGHT);
        tile[2].position = sf::Vector2f(Tile::getX() * Tile::WIDTH + Tile::WIDTH , Tile::getY() * Tile::HEIGHT + Tile::HEIGHT);
        tile[3].position = sf::Vector2f(Tile::getX() * Tile::WIDTH, Tile::getY() * Tile::HEIGHT + Tile::HEIGHT);

        sf::Color tileColor;
        if (Tile::getMaterial() == Tile::dirt) {
            tileColor = sf::Color(160,82,45);
        } else if (Tile::getMaterial() == Tile::snow) {
            //tileColor = sf::Color::White;
            tileColor = sf::Color(105,105,105);
        } else if (Tile::getMaterial() == Tile::grass) {
            tileColor = sf::Color::Green;
        }

        tile[0].color = tileColor;
        tile[1].color = tileColor;
        tile[2].color = tileColor;
        tile[3].color = tileColor;

        tx->draw(tile);
*/
    }

    sf::Color hsv(int hue, float sat, float val)
    {
      hue %= 360;
      while(hue<0) hue += 360;

      if(sat<0.f) sat = 0.f;
      if(sat>1.f) sat = 1.f;

      if(val<0.f) val = 0.f;
      if(val>1.f) val = 1.f;

      int h = hue/60;
      float f = float(hue)/60-h;
      float p = val*(1.f-sat);
      float q = val*(1.f-sat*f);
      float t = val*(1.f-sat*(1-f));

      switch(h)
      {
          default:
          case 0:
          case 6: return sf::Color(val*255, t*255, p*255);
          case 1: return sf::Color(q*255, val*255, p*255);
          case 2: return sf::Color(p*255, val*255, t*255);
          case 3: return sf::Color(p*255, q*255, val*255);
          case 4: return sf::Color(t*255, p*255, val*255);
          case 5: return sf::Color(val*255, p*255, q*255);
      }
    }
}
