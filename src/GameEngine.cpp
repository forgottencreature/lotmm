#include "GameEngine.hpp"

#include <memory>
#include <iostream>
#include "GameState.hpp"

#include "IntroState.hpp"
#include "MenuState.hpp"

GameEngine::GameEngine( const std::string& title, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen ) :	m_resume( false ),	m_running( false ),	m_fullscreen( fullscreen ){
	int flags = 0;

	if( fullscreen )
		flags = sf::Style::Fullscreen;
	else
		flags = sf::Style::Default;

	// Create render window for the main app
	app_window.create( sf::VideoMode( width, height, bpp ), title, flags, sf::ContextSettings(0,0,8,0,0) );
	app_window.setFramerateLimit( 60 );

	app_window.resetGLStates();

	screen = sfg::Window::Create();
	screen->SetTitle("SFML Canvas");
	//This offset needs to be looked into, why can't it be at the top left , (0,0)
	screen->SetPosition(sf::Vector2f(-10.f,-34.f));

	canvas = sfg::Canvas::Create();
	screen->Add(canvas);

	canvas->SetRequisition(sf::Vector2f(1280.f,800.f));
	desktop.Add(canvas);
	desktop.Update(0.f);

	sf::Vector2f center(width/2,height/2);
	sf::Vector2f halfsize(width,height);
	sf::View screenView(center,halfsize);
	canvas->SetView(screenView);


	// Set the view
	/* screen.setView(screenView); */

	std::cout << "GameEngine Init" << std::endl;
}

void GameEngine::run( std::unique_ptr<GameState> state ){
	m_running = true;

	m_states.push( std::move( state ) );
}

void GameEngine::nextState(){
	if(m_resume){
		// cleanup the current state
		if ( !m_states.empty() ){
			m_states.pop();
		}
		// resume previous state
		if ( !m_states.empty() ){
			m_states.top()->resume();
		}
		m_resume = false;
	}

	// there needs to be a state
	if ( !m_states.empty() ){
		std::unique_ptr<GameState> temp = m_states.top()->next();

		// only change states if there's a next one existing
		if( temp != 0 ){
			// replace the running state
			if( temp->isReplacing() )
				m_states.pop();
			// pause the running state
			else
				m_states.top()->pause();

			m_states.push( std::move( temp ) );
		}
	}
}

void GameEngine::lastState(){
	m_resume = true;
}

void GameEngine::update(){
	// let the state update the game
	m_states.top()->update();
}

void GameEngine::draw(){
	// let the state draw the screen
	m_states.top()->draw();
}
