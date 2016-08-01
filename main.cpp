#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "Player.hpp"
#include "TileMap.hpp"
#include "Camera.hpp" 

int main() {

	/* Initialize random seed */
    srand ( time(NULL) );

    /* What are these for? I think I may have removed all offset functionality. */
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

    /* Instantiate the player */
    GAME::Player player;

    /* Place the player at the default location */
    player.warp(200,28);

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

        /* Point the camera at our player sprite */
        camera.setTarget(player.getSpritePosition());

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
            player.move(GAME::Dir::Left);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.move(GAME::Dir::Down);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.move(GAME::Dir::Right);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.move(GAME::Dir::Up);
        }

        player.update();

        texture.clear(sf::Color::Blue);
        
        /* Draw the tile map */
        map.DrawVertexArray(&window, offset);
        map.DrawTileGrid(&window, offset);


        /* Draw our character */
        player.draw(&window);

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

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Z ) { 
                    /* Toggle the show grid bool */
                    map.ToggleGrid();
                }
            }
        }

        /* Calculations for FPS */
        sf::Time time1 = clock.getElapsedTime();
        sf::Time time2 = clock.restart();
        float fps = 1.f / time1.asSeconds();

        /* Output FPS */
        //if(fps < 30) 
        //{
            std::cout << "FPS: " << fps << "\n";
        //}

        window.display();
    }

	return 0;
}