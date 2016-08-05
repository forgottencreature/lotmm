#include <memory>
#include <iostream>
#include <math.h>
#include <ctime>
#include <SFML/System.hpp>

#include "PlayState.hpp"
#include "MenuState.hpp"
#include "GameEngine.hpp"


PlayState::PlayState( GameEngine& game, bool replace ) : GameState( game, replace )
{
    sf::Vector2f center(1280/2,720/2);
	sf::Vector2f halfsize(1280,720);
    sf::View screenView(center,halfsize);
    m_game.screen.setView(screenView);

    std::cout << "PlayState Init" << std::endl;

    tileMap.generate();
    /*
    tileMap.removeTile(sf::Vector2<int>(0,0));
    tileMap.removeTile(sf::Vector2<int>(0,1));
    tileMap.removeTile(sf::Vector2<int>(1,0));
    tileMap.removeTile(sf::Vector2<int>(1,1));
    */

    player.create(sf::Vector2<int>(5,5));

    //player.setGridPosition(0,0,&tileMap);
    //player.update(&tileMap); // Can I move this into the Player object somehow? Look into it.
}

void PlayState::pause()
{
}

void PlayState::resume()
{
}

void PlayState::update()
{
    float elapsedTime = gameClock.restart().asSeconds();

    //std::cout << "grid position set to  " << player.gridX << " " << player.gridY << "\n";
/*
    for (int i = 0; i < npcManager.npcs.size(); i++) {
        npcManager.npcs[i]->update(elapsedTime);
    }

    npcManager.checkCollision(m_game.textureManager);
*/

    //player.update(&tileMap,elapsedTime);
    player.update();
    PlayState::updateInput();
}

void PlayState::draw()
{

    m_game.screen.clear(sf::Color::Black);

    /* Draw the tiles */
    m_game.screen.draw(tileMap.getTiles());

    /* Draw the grid lines. These have to be drawn after so that the tiles do not cover them up. */
    m_game.screen.draw(tileMap.getGridLines());

    /* Draw our character */
    m_game.screen.draw(player.getSprite());

	m_game.screen.display();
}

void PlayState::updateInput()
{

    /* Key Bindings */
    /*
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        sf::Vector2<int> pos = player.getGridPosition();
        sf::Vector2<int> newPos = sf::Vector2<int>(pos.x,pos.y-1);
        tileMap.digTile(newPos);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sf::Vector2<int> pos = player.getGridPosition();
        sf::Vector2<int> newPos = sf::Vector2<int>(pos.x-1,pos.y);
        tileMap.digTile(newPos);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        sf::Vector2<int> pos = player.getGridPosition();
        sf::Vector2<int> newPos = sf::Vector2<int>(pos.x,pos.y+1);
        tileMap.digTile(newPos);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sf::Vector2<int> pos = player.getGridPosition();
        sf::Vector2<int> newPos = sf::Vector2<int>(pos.x+1,pos.y);
        tileMap.digTile(newPos);
    }
*/

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.setMovement("LEFT");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player.setMovement("DOWN");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.setMovement("RIGHT");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player.setMovement("UP");
    }

    sf::Event event;
    while( m_game.screen.pollEvent( event ) )
	{
		switch( event.type )
		{
			case sf::Event::Closed:
				m_game.quit();
				break;

			case sf::Event::KeyPressed:
				switch( event.key.code )
				{
					case sf::Keyboard::Escape:
						m_game.quit();
						break;
                    case sf::Keyboard::Z:
                        tileMap.toggleGrid();
                        break;
					case sf::Keyboard::M:
						m_next = m_game.build<MenuState>( false );
						break;
                    case sf::Keyboard::Space:
                        break;
                    default:
                        break;
				}
				break;
            default:
                break;
		}

        if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
        {
            int mouseWheelDelta = (int) event.mouseWheelScroll.delta;

            //std::cout << mouseWheelDelta << "\n";

            if(mouseWheelDelta > 0)
            {
                this->screenView.zoom(.90f);
            }
            else if(mouseWheelDelta < 0)
            {
                this->screenView.zoom(1.10f);
            }
        }

	}


}
