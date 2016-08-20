#include <memory>
#include <iostream>

#include "IntroState.hpp"
#include "MainMenuState.hpp"
#include "GameEngine.hpp"

IntroState::IntroState( GameEngine& game, bool replace ) : GameState( game, replace ){
	m_bgTex.create(1280,760);
	m_bgTex.loadFromFile( "assets/img/splashscreen.png" );
	m_bg.setTexture( m_bgTex, true );

	// start off opaque
	m_alpha = sf::Color( 0, 0, 0, 255 );

	// fill the fader surface with black
	m_fader.setFillColor( m_alpha );
	m_fader.setSize( static_cast<sf::Vector2f>( m_bgTex.getSize() ) );

	std::cout << "IntroState Init" << std::endl;
}

void IntroState::pause(){
	std::cout << "IntroState Pause" << std::endl;
}

void IntroState::resume(){
	std::cout << "IntroState Resume" << std::endl;
}

void IntroState::update(){
	sf::Event event;

	while( m_game.m_window.pollEvent( event ) ){
		switch( event.type ){
			case sf::Event::Closed:
				m_game.quit();
				break;

			case sf::Event::KeyPressed:{
					switch( event.key.code ){
						case sf::Keyboard::Space:
							m_next = m_game.build<MainMenuState>( true );
							break;

						case sf::Keyboard::Escape:
							m_game.quit();
							break;
						default:
							break;
					}
					break;
		 }
			default:
					break;
		}
	}

	if( m_alpha.a != 0 )
		m_alpha.a--;

	m_fader.setFillColor( m_alpha );
}

void IntroState::draw(){
	// Clear the previous drawing
	m_game.m_window.clear();

	m_game.m_window.draw( m_bg );

	// no need to draw if it's transparent
	if( m_alpha.a != 0 )
		m_game.m_window.draw( m_fader );

	m_game.m_window.display();
}

