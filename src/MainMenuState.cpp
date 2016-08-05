#include <memory>
#include <iostream>

#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "IntroState.hpp"
#include "GameEngine.hpp"


MainMenuState::MainMenuState( GameEngine& game, bool replace ) : GameState( game, replace )
{
    m_bgTex.create(800,600);
	m_bgTex.loadFromFile( "assets/img/mainmenu.png" );

	m_bg.setTexture( m_bgTex, true );

	std::cout << "MenuState Init" << std::endl;
}

void MainMenuState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MainMenuState::resume()
{
	std::cout << "MenuState Resume" << std::endl;
}

void MainMenuState::update()
{
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
                        m_next = m_game.build<IntroState>( true );
                        //m_game.lastState();
						//m_game.quit();
						break;
                    case sf::Keyboard::N:
                        m_next = m_game.build<PlayState>( true );
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void MainMenuState::draw()
{
	// Clear the previous drawing
	m_game.screen.clear();
	m_game.screen.draw( m_bg );
	m_game.screen.display();
}
