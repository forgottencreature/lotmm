#ifndef GAMEOVERSTATE_HPP
#define GAMEOVERSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.hpp"

class GameEngine;

class GameOverState : public GameState{
	public:
		GameOverState( GameEngine& game, bool replace = true );

		void pause();
		void resume();

		void update();
		void draw();

	private:

		sf::Texture m_bgTex;
		sf::Sprite m_bg;
		sf::SoundBuffer m_soundBuff;
		sf::Sound m_music;
};

#endif // GAMEOVERSTATE_HPP
