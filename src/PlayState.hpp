#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.hpp"
#include "TextureManager.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Camera.hpp"

class GameEngine;
//class TileMap;

class PlayState : public GameState{
	public:

		PlayState( GameEngine& game, bool replace = true );

		void pause();
		void resume();

		void update();
		void draw();
		void updateInput();

		sf::Clock gameClock;

	private:
		TileMap tileMap;
		Player player;
		Camera camera;

		sf::Texture m_bgTex;
		sf::Sprite m_bg;

		sf::View screenView;

		sf::Music m_music;

		float time;


};

#endif // PLAYSTATE_HPP
