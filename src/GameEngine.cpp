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
	app_window.create( sf::VideoMode( width, height, bpp ), title, sf::Style::Default);
    app_window.resetGLStates();
	//app_window.setFramerateLimit( 60 );


	screen = sfg::Window::Create();
	screen->SetTitle("SFML Canvas");
    screen->SetPosition(sf::Vector2f(0.f,0.f));
	//This offset needs to be looked into, why can't it be at the top left , (0,0)
	//screen->SetPosition(sf::Vector2f(-10.f,-34.f));

	canvas = sfg::Canvas::Create();
	screen->Add(canvas);

	canvas->SetRequisition(sf::Vector2f(1280.f/2,800.f/2));
    if(desktop.LoadThemeFromFile("data/example.theme")) {
        std::cout << "loaded sfgui theme" << std::endl;
    } else {
        std::cout << "DID NOT FUCKING loaded sfgui theme" << std::endl;
    }

	desktop.Add(canvas);
	desktop.Update(0.f);

	sf::Vector2f center(width/2,height/2);
	sf::Vector2f halfsize(width,height);
	sf::View screenView(center,halfsize);
	canvas->SetView(screenView);

	m_fps_counter = 0;
	m_fps_clock.restart();

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
    // Update the GUI every 5ms
	auto microseconds = clock.getElapsedTime().asMicroseconds();
	if( microseconds > 5000 ) {
		desktop.Update(static_cast<float>( microseconds ) / 1000000.f);
		clock.restart();
		app_window.setActive( true );
	}

	// let the state update the game
	m_states.top()->update();


	auto frame_time = frame_time_clock.getElapsedTime().asMicroseconds();
	frame_time_clock.restart();

	frame_times[ frame_times_index ] = frame_time;
	frame_times_index = ( frame_times_index + 1 ) % 5000;

	if( m_fps_clock.getElapsedTime().asMicroseconds() >= 1000000 ) {
		m_fps_clock.restart();

		sf::Int64 total_time = 0;

		for( std::size_t index = 0; index < 5000; ++index ) {
			total_time += frame_times[index];
		}

		std::stringstream sstr;
		sstr << "SFGUI test -- FPS: " << m_fps_counter << " -- Frame Time (microsecs): min: "
			 << *std::min_element( frame_times, frame_times + 5000 ) << " max: "
			 << *std::max_element( frame_times, frame_times + 5000 ) << " avg: "
			 << static_cast<float>( total_time ) / 5000.f;

		app_window.setTitle( sstr.str() );

		m_fps_counter = 0;
	}

	++m_fps_counter;


}

void GameEngine::draw(){
	// let the state draw the screen
	m_states.top()->draw();
}
