#include <memory>
#include <iostream>

#include "MenuState.hpp"

MenuState::MenuState( GameEngine& game, bool replace ) : GameState( game, replace )
{
	m_bgTex.loadFromFile( "assets/img/menu.png" );

	m_bg.setTexture( m_bgTex, true );

	sf::Vector2f center(1280/2,800/2);
	sf::Vector2f halfsize(1280,800);
	sf::View screenView(center,halfsize);

	// Set the view
	m_game.app_window.setView(screenView);

	std::cout << "MenuState Init" << std::endl;
}

void MenuState::pause()
{
	std::cout << "MenuState Pause" << std::endl;
}

void MenuState::resume()
{
	std::cout << "MenuState Resume" << std::endl;
}

void MenuState::update()
{
	sf::Event event;

	while( m_game.app_window.pollEvent( event ) )
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
						m_game.lastState();
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

void MenuState::draw()
{
	// Clear the previous drawing
	m_game.app_window.clear();
	m_game.app_window.draw( m_bg );
	m_game.app_window.display();
}

