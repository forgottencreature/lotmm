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
	m_soundBuff.loadFromFile("assets/audio/main_menu_2.ogg");
	m_music.setBuffer(m_soundBuff);
	m_music.play();
	m_music.setLoop(true);

	m_bg.setTexture( m_bgTex, true );

	sf::Vector2f center(1280/2,800/2);
	sf::Vector2f halfsize(1280,800);
	sf::View screenView(center,halfsize);

	// Set the view
	m_game.app_window.setView(screenView);


	std::cout << "MainMenuState Init" << std::endl;
}

void MainMenuState::pause()
{
	std::cout << "MainMenuState Pause" << std::endl;
}

void MainMenuState::resume()
{
	std::cout << "MainMenuState Resume" << std::endl;
}

void MainMenuState::update()
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
						m_music.stop();
						m_next = m_game.build<IntroState>( true );
						//m_game.lastState();
						//m_game.quit();
						break;
					case sf::Keyboard::N:
						m_music.stop();
						m_next = m_game.build<PlayState>( true );
						break;
					case sf::Keyboard::P:
						if (m_music.getStatus() == sf::Music::Playing) {
							m_music.pause();
						} else {
							m_music.play();
						}
						break;
					case sf::Keyboard::Q:
						m_game.quit();
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
	m_game.app_window.clear();
	m_game.app_window.draw( m_bg );
	m_game.app_window.display();
}

