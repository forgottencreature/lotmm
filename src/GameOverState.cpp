#include <memory>
#include <iostream>

#include "GameOverState.hpp"
#include "MainMenuState.hpp"
#include "GameEngine.hpp"


GameOverState::GameOverState( GameEngine& game, bool replace ) : GameState( game, replace ){
	m_bgTex.create(800,600);
	if(m_game.getWonGame()){
	m_bgTex.loadFromFile( "assets/img/gameover_win.png" );
	/* m_soundBuff.loadFromFile("assets/audio/main_menu_2.ogg"); */
	}
	else{
	m_bgTex.loadFromFile( "assets/img/gameover_lose.png" );
	/* m_soundBuff.loadFromFile("assets/audio/main_menu_2.ogg"); */
	}
	/* m_music.setBuffer(m_soundBuff); */
	/* m_music.setVolume(25.f); */
	/* m_music.play(); */
	/* m_music.setLoop(true); */

	m_bg.setTexture( m_bgTex, true );

	sf::Vector2f center(1280/2,800/2);
	sf::Vector2f halfsize(1280,800);
	sf::View screenView(center,halfsize);

	// Set the view
	m_game.m_window.setView(screenView);


	std::cout << "GameOverState Init" << std::endl;
}

void GameOverState::pause(){
	std::cout << "GameOverState Pause" << std::endl;
}

void GameOverState::resume(){
	std::cout << "GameOverState Resume" << std::endl;
}

void GameOverState::update(){
	sf::Event event;

	while( m_game.m_window.pollEvent( event ) ){
		switch( event.type ){
			case sf::Event::Closed:
				m_game.quit();
				break;

			case sf::Event::KeyPressed:
				switch( event.key.code ){
					case sf::Keyboard::Escape:
						/* m_music.stop(); */
						m_next = m_game.build<MainMenuState>( true );
						//m_game.lastState();
						//m_game.quit();
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

void GameOverState::draw(){
	// Clear the previous drawing
	m_game.m_window.clear();
	m_game.m_window.draw( m_bg );
	m_game.m_window.display();
}

