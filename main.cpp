#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "TileMap.hpp"
#include "Camera.hpp" 


struct Dir {
    enum Type {Up, Right, Down, Left};
};

 /* convert this to a class/object when I get a chance */
struct GuyStruct 
{
    float x, y;
    int gridX, gridY;
    float speed = 4.0f;

    bool isMoving() const
    {
        //std::cout << "is moving bool: " << !(x == gridX * GAME::Tile::WIDTH && y == gridY * GAME::Tile::HEIGHT) << "\n";
        return !(x == gridX * GAME::Tile::WIDTH && y == gridY * GAME::Tile::HEIGHT);
    }

    void warp(int newGridX, int newGridY)
    {
        gridX = newGridX;
        gridY = newGridY;

        x = newGridX * GAME::Tile::WIDTH;
        y = newGridY * GAME::Tile::WIDTH;
    }

    void move(const Dir::Type dir)
    {
        if (isMoving())
        {
            return;
        }

        if (dir == Dir::Up)
        {
            gridY -= 1;
        }
        else if (dir == Dir::Down)
        {
            gridY += 1;
        }
        if (dir == Dir::Left)
        {
            gridX -= 1;
        }
        else if (dir == Dir::Right)
        {
            gridX += 1;
        }

        //std::cout << "X,Y: " << gridX << "," << gridY << "\n";
    }

    void update()
    {
        /* Move right */
        if (x < gridX * GAME::Tile::WIDTH)
        {
            x = std::min(x + speed, float(gridX * GAME::Tile::WIDTH));
        }

        /* Move left */
        else if (x > gridX * GAME::Tile::WIDTH)
        {
            x = std::max(x - speed, float(gridX * GAME::Tile::WIDTH));
        }

        /* Move Down */
        if (y < gridY * GAME::Tile::WIDTH)
        {
            y = std::min(y + speed, float(gridY * GAME::Tile::WIDTH));
        }

        /* Move Up */
        else if (y > gridY * GAME::Tile::WIDTH) 
        {
            y = std::max(y - speed, float(gridY * GAME::Tile::WIDTH));
        }

    }

    sf::Vector2f getCoors() const 
    {
        return sf::Vector2f(x,y); 
    }

};

int main() {

	/* Initialize random seed */
    srand ( time(NULL) );

    int speed = GAME::Tile::WIDTH;
    bool left;
    float offset = 0.00f; // wtf is this even doing?

    /* Game clock declarations */
	sf::Clock clock;
    sf::Time time;
    float lastTime = 0;

    /* Set up our view */
    sf::Vector2f Center(1800, 300);
    sf::Vector2f HalfSize(640, 360);
    sf::View View(Center, HalfSize);

    /* Set up our camera */
    GAME::camera camera;
    camera.move(Center);
    //camera.move(sf::Vector2f(8,8));

    /* Set context */
	sf::ContextSettings(0,0,4,2,0);

    /* Declare and create a new window */
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Window");

    /* Limit the framerate to 60 frames per second (this step is optional) */
    //window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);

    /* Activate the window for OpenGL rendering */
    window.setActive();


    /* Create a red dot "character" */
    sf::RectangleShape guy;

    /* Instantiate the struct I created. I have to merge the struct & the rest of the chacacter functionality into an object/class */
    GuyStruct guyStruct;
    guyStruct.warp(200,28);

    guy.setPosition(guyStruct.getCoors());
    guy.setSize(sf::Vector2f(GAME::Tile::WIDTH, GAME::Tile::HEIGHT));
    guy.setFillColor(sf::Color::Red);
    //guy.setFillColor(sf::Color(105,105,105));
    //guy.setOutlineColor(sf::Color(100,200,100));
    guy.setOutlineThickness(0);
    //guy.setPosition(Tile::WIDTH*10, Tile::WIDTH*10);
    //guy.setPosition(sf::Vector2f(0,0));
    guy.setPosition(Center);

    /* 
        Create a new render-texture for our background. Set it to the same size as the Tile Map 
        ... not sure if I need this right now, as I'm no longer using an image for the background
    */
    sf::RenderTexture texture;
    if (!texture.create(GAME::TileMap::MAX_X*GAME::Tile::WIDTH, GAME::TileMap::MAX_Y*GAME::Tile::HEIGHT))
        return -1;

    /* Set our background color on the texture */
    texture.clear(sf::Color::Blue);

    /* Initialize the tile map */
    GAME::TileMap map;

    /* Generate the tile map data */
    map.GenerateMap();

    /* Draw the tile map */
    map.DrawVertexArray(&window, offset);
    map.DrawTileGrid(&window, offset);

    /* Create a sprite from the texture. 
        NOTE this is not really doing anything important ATM
    */
    sf::Sprite tiledBG(texture.getTexture());
    window.draw(tiledBG);

    /* The main loop - ends as soon as the window is closed */
    while (window.isOpen()) 
    {
        window.clear();

        /* Point the camera at our guy */
        camera.setTarget(guy.getPosition());

        /* Update & set the view */
        View.move(camera.update());
        window.setView(View);

        //window.draw(tiledBG);

         /* Key Bindings */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
             window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            left = true;
            offset -= 10;
            guyStruct.move(Dir::Left);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            guyStruct.move(Dir::Down);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            left = false;
            offset += 10;
            guyStruct.move(Dir::Right);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            guyStruct.move(Dir::Up);
        }

        guyStruct.update();
        guy.setPosition(guyStruct.getCoors());

        texture.clear(sf::Color::Blue);
        
        /* Draw the tile map */
        map.DrawVertexArray(&window, offset);
        map.DrawTileGrid(&window, offset);


        /* Draw our character */
        window.draw(guy);

        /* Event processing */
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }

            if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                int mouseWheelDelta = (int) event.mouseWheelScroll.delta;
                if(mouseWheelDelta > 0) 
                {
                    View.zoom(.90f);
                } 
                else if(mouseWheelDelta < 0)
                {
                    View.zoom(1.10f);
                }
            }
        }

        /* Calculations for FPS */
        sf::Time time1 = clock.getElapsedTime();
        sf::Time time2 = clock.restart();
        float fps = 1.f / time1.asSeconds();

        /* Output FPS */
        if(fps < 30) 
        {
            //std::cout << "FPS: " << fps << "\n";
        }

        window.display();
    }

	return 0;
}