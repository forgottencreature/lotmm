#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <stack>
#include <string>
#include <memory>
#include <iostream>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Renderers.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"

class GameState;
class TextureManager;

class GameEngine{
	public:
		GameEngine( const std::string& title, const unsigned int width = 1280, const unsigned int height = 800, const unsigned int bpp = 32, const bool fullscreen = false );

		void run( std::unique_ptr<GameState> state );

		void nextState();
		void lastState();

		void update();
		void draw();

		bool running() { return m_running; }
		void quit() { m_running = false; }

		template <typename T>
			std::unique_ptr<T> build( bool replace = true );

        sfg::SFGUI sfgui_wrap;
		std::shared_ptr<sfg::Window> screen;
		std::shared_ptr<sfg::Canvas> canvas;
		sfg::Desktop desktop;

        unsigned int m_fps_counter;
        sf::Clock m_fps_clock;

        sf::Clock clock;
        sf::Clock frame_time_clock;

        sf::Int64 frame_times[5000];
        std::size_t frame_times_index = 0;

		sf::RenderWindow m_window;

		TextureManager textureManager;

        bool getDevMode() const { return m_devMode; }
        void toggleDevMode();

        void OnHideWindowClicked();

				bool getWonGame() const {return m_wonGame;}
				void setWonGame( bool win ){ m_wonGame = win;}

	private:
		// the stack of states
		std::stack<std::unique_ptr<GameState> > m_states;
		bool m_resume;

		bool m_running;
		bool m_fullscreen;

		bool m_wonGame=false;

        bool m_devMode = false;
};

template <typename T>
std::unique_ptr<T> GameEngine::build( bool replace ){
	return std::move( std::unique_ptr<T>( new T( *this, replace ) ) );
}

#endif // GAMEENGINE_HPP
