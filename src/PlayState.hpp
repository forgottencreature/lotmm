#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Input.hpp>
#include "GameState.hpp"
#include "TextureManager.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Camera.hpp"

class GameEngine;
//class TileMap;

using thor::Action;

class PlayState : public GameState{
	public:

		PlayState( GameEngine& game, bool replace = true );

		void pause();
		void resume();

		void update();
		void draw();
		void updateInput();

		sf::Clock gameClock;
		int wall = 0;
		int wallCount = 50;
		int wallReset = 50;

	private:
		TileMap tileMap;
		Player player;
		Camera camera;

        thor::ActionMap<std::string> actionMap;
        thor::ActionMap<std::string>::CallbackSystem callbackSystem;

		sf::Texture m_bgTex;
		sf::Sprite m_bg;

		sf::View screenView;

		sf::Music m_music;

		float time;

		std::shared_ptr<sfg::Window> devConsole_screen;
		std::shared_ptr<sfg::Canvas> devConsole_canvas;
        sfg::Label::Ptr playerDamageScaleLabel;
        sfg::Adjustment::Ptr playerDamageAdjustment;
		sfg::Label::Ptr wallResetScaleLabel;
		sfg::Adjustment::Ptr wallResetAdjustment;

        void createDevConsole();
        void registerActions();
		void stateChangeCleanup();

        void onZoom(thor::ActionContext<std::string> context);

        void playerDamageScaleAdjustmentChange();
		void wallResetAdjustmentChange();
        void onResetBtnClicked();
        void onToggleGridBtnClicked();
		void onHideWindowClicked();

};

#endif // PLAYSTATE_HPP
