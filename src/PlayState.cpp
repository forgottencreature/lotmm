#include <memory>
#include <iostream>
#include <math.h>
#include <ctime>
#include <SFML/System.hpp>

#include "PlayState.hpp"
#include "MainMenuState.hpp"
#include "MenuState.hpp"


PlayState::PlayState( GameEngine& game, bool replace ) : GameState( game, replace ){
	sf::Vector2f center(1280/2,800/2);
	sf::Vector2f halfsize(1280,800);
	screenView = sf::View(center,halfsize);

	camera.move(sf::Vector2f(5,5));

	m_game.canvas->SetView(screenView);

	tileMap.generate();

	player.create(sf::Vector2<int>(0,0));

	camera.setTarget(player.getSprite().getPosition());

	m_music.openFromFile("assets/audio/AlexsBeatportHit1.ogg");
	m_music.play();
	m_music.setLoop(true);

    devConsole_screen = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND | sfg::Window::Style::CLOSE);
    devConsole_screen->SetId("devConsole");
    devConsole_screen->SetTitle("Dev Console");
    devConsole_screen->SetPosition(sf::Vector2f(100.f,200.f));

    devConsole_canvas = sfg::Canvas::Create();
    devConsole_screen->Add(devConsole_canvas);
    devConsole_canvas->SetRequisition(sf::Vector2f(200.f,300.f));

    m_game.desktop.Add(devConsole_screen);
    m_game.desktop.Update(0.f);

    devConsole_screen->GetSignal( sfg::Window::OnCloseButton ).Connect( std::bind( &PlayState::OnHideWindowClicked, this ) );

    std::cout << "PlayState cpp Init" << std::endl;
}

void PlayState::pause(){
}

void PlayState::resume(){
}

void PlayState::update(){

    m_game.desktop.BringToFront(devConsole_screen);

	float elapsedTime = gameClock.restart().asSeconds();

	player.update(&tileMap,elapsedTime);

	/* Setting the camera to follow the player */
	camera.setTarget(player.getSprite().getPosition()-sf::Vector2f(1280/2,800/2)+sf::Vector2f(32/2,32/2));

	/* Move the view to where the camera wants it to go */
	screenView.move(camera.update());

	/* This works, but disabling the camera for the time being */
	m_game.canvas->SetView(screenView);

	PlayState::updateInput();
}

void PlayState::draw(){

	m_game.m_window.clear(sf::Color::Black);

	/* Draw the tiles */
	m_game.canvas->Bind();
	m_game.canvas->Clear(sf::Color(75,0,130));

	m_game.canvas->Draw(tileMap.getFloor());

	/* Draw the floor */
	m_game.canvas->Draw(tileMap.getBlocks());

	/* Draw the grid lines. These have to be drawn after so that the tiles do not cover them up. */
	m_game.canvas->Draw(tileMap.getGridLines());

	/* Draw our character */
	m_game.canvas->Draw(player.getSprite());

	m_game.canvas->Display();
    m_game.canvas->Unbind();

	m_game.m_window.setActive(true);

    m_game.sfgui_wrap.Display(m_game.m_window);


	m_game.m_window.display();
}

void PlayState::updateInput(){

	/* Key Bindings */

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x,pos.y-1);
		tileMap.digBlock(newPos);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x-1,pos.y);
		tileMap.digBlock(newPos);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x,pos.y+1);
		tileMap.digBlock(newPos);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x+1,pos.y);
		tileMap.digBlock(newPos);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		player.setMovement("LEFT");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		player.setMovement("DOWN");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		player.setMovement("RIGHT");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		player.setMovement("UP");
	}

	sf::Event event;
	while( m_game.m_window.pollEvent( event ) ){
		switch( event.type ){
			case sf::Event::Closed:
				m_game.quit();
				break;

			case sf::Event::KeyPressed:
				switch( event.key.code ){
					case sf::Keyboard::Escape:
						m_music.stop();
                        stateChangeCleanup();
						m_next = m_game.build<MainMenuState>( true );
						break;
					case sf::Keyboard::Z:
						tileMap.toggleGrid();
						break;
					case sf::Keyboard::M:
						m_next = m_game.build<MenuState>( false );
						break;
					case sf::Keyboard::Space:
						break;
                    case sf::Keyboard::P:
                        OnHideWindowClicked();
                        break;
					default:
						break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left){
				}
				else if (event.mouseButton.button == sf::Mouse::Right){
				}
			default:
				break;
		}

		if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
			int mouseWheelDelta = (int) event.mouseWheelScroll.delta;

			if(mouseWheelDelta > 0){
				screenView.zoom(.90f);
			}
			else if(mouseWheelDelta < 0){
				screenView.zoom(1.10f);
			}
		}

        m_game.desktop.HandleEvent( event );
	}
}

void PlayState::stateChangeCleanup() {
    m_game.desktop.Remove(devConsole_screen);
    m_game.desktop.Remove(devConsole_canvas);
    devConsole_screen.reset();
    devConsole_canvas.reset();
    std::cout << "Desktop Cleanup" << std::endl;

}

void PlayState::OnHideWindowClicked() {
    devConsole_screen->Show( !devConsole_screen->IsLocallyVisible() );
}