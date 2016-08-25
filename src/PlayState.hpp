#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Input.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Animations.hpp>
#include "GameState.hpp"
#include "TextureManager.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "Camera.hpp"

class GameEngine;
//class TileMap;

using thor::Action;

struct ZoomAction
{
    explicit ZoomAction(sf::View& screenView)
    : screenView(screenView)
    {
    }

    void operator() (thor::ActionContext<std::string> context)
    {
        sf::Event event = *context.event;

        if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
            int mouseWheelDelta = (int) event.mouseWheelScroll.delta;

            if(mouseWheelDelta > 0){
                screenView.zoom(.90f);
            }
            else if(mouseWheelDelta < 0){
                screenView.zoom(1.10f);
            }
        }
    }

    sf::View& screenView;
};

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
        thor::ParticleSystem particleSystem;

        sf::Clock particleClock;

		sf::Texture m_bgTex;
		sf::Sprite m_bg;
        sf::Texture particleTexture;

		sf::View screenView;

		sf::Music m_music;

		float time;
		const float dTime = 0.01f;
		float currentTime;
		float timeAccumulator = 0.0f;
		

		std::shared_ptr<sfg::Window> devConsole_screen;
		std::shared_ptr<sfg::Canvas> devConsole_canvas;
        sfg::Label::Ptr playerDamageScaleLabel;
        sfg::Adjustment::Ptr playerDamageAdjustment;
		sfg::Label::Ptr wallResetScaleLabel;
		sfg::Adjustment::Ptr wallResetAdjustment;

        void createParticleTexture(int w, int h);
        void animateParticles();
        void createDevConsole();
        void registerActions();
		void stateChangeCleanup();

        //static void onZoom(thor::ActionContext<std::string> context, sf::View& screenView);

        void playerDamageScaleAdjustmentChange();
		void wallResetAdjustmentChange();
        void onResetBtnClicked();
        void onToggleGridBtnClicked();
		void onHideWindowClicked();

};

#endif // PLAYSTATE_HPP
