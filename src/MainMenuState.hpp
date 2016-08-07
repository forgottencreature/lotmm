#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class GameEngine;

class MainMenuState : public GameState
{
public:
	MainMenuState( GameEngine& game, bool replace = true );

	void pause();
	void resume();

	void update();
	void draw();

private:

	sf::Texture m_bgTex;
	sf::Sprite m_bg;
};

#endif // MAINMENUSTATE_HPP
