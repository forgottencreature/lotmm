#include <memory>
#include <iostream>
#include <math.h>
#include <ctime>
#include <SFML/System.hpp>

#include "PlayState.hpp"
#include "MainMenuState.hpp"
#include "GameOverState.hpp"
#include "MenuState.hpp"


PlayState::PlayState( GameEngine& game, bool replace ) : GameState( game, replace ){
	sf::Vector2f center(1280/2,800/2);
	sf::Vector2f halfsize(1280,800);
	screenView = sf::View(center,halfsize);

	camera.move(sf::Vector2f(5,5));

	m_game.canvas->SetView(screenView);

	tileMap.generate();

	player.create(sf::Vector2<int>(10,0));

	camera.setTarget(player.getSprite().getPosition());

	m_music.openFromFile("assets/audio/AlexsBeatportHit1.ogg");
	m_music.play();
	m_music.setLoop(true);

    if(m_game.getDevMode()) {
        createDevConsole();
    }

    /* Register the player actions using Thor */
    registerActions();

    /* Create our texture for the particles */
    createParticleTexture(6,6);

    /* Attach the texture to the particle system */
    particleSystem.setTexture(particleTexture);

    /* Add neccessary asthetics to particles */
    animateParticles();

    std::cout << "PlayState cpp Init" << std::endl;
}

void PlayState::pause(){
}

void PlayState::resume(){
}

void PlayState::update(){

    // Update particle system
    particleSystem.update(particleClock.restart());


    /* Need this line to force the dev console to top, regardless of focus */
    m_game.desktop.BringToFront(devConsole_screen);

	float elapsedTime = gameClock.restart().asSeconds();
	frameTime = elapsedTime;
	timeAccumulator+=frameTime;

	//While we're behind in physics keep updating, or if we are ahead and don't need to, don't.
	//Put all the updating here
	while(timeAccumulator >= dTime){

		player.update(&tileMap,elapsedTime);

		//Delay 100 ticks for wall move
		wallCount--;
		if(wallCount<=0){
			wall++;
			wallCount=wallReset;
		}
		// Player is at or behind wall, game over
		if(player.getCurrentGridPosition().x <= wall){
			m_game.setWonGame(false);
			m_music.stop();
			stateChangeCleanup();
			m_next = m_game.build<GameOverState>( true );
		}
		//Player got to the right, win game!
		else if(player.getCurrentGridPosition().x == TileMap::MAX_X - 1){
			m_game.setWonGame(true);
			m_music.stop();
			stateChangeCleanup();
			m_next = m_game.build<GameOverState>( true );
		}

		//Subtract our per fram time from the accumulator
		timeAccumulator-=dTime;
		//Total time running, might want in frames too?
		time+=dTime;
	}

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

	/* Draw wall */
	sf::RectangleShape rectangle(sf::Vector2f(32*(wall+1),32*100));
	rectangle.setFillColor(sf::Color(20,20,20));
	rectangle.setPosition(0,0);
	m_game.canvas->Draw(rectangle);

    /* Draw particles */
    m_game.canvas->Draw(particleSystem);

	m_game.canvas->Display();
    m_game.canvas->Unbind();

	m_game.m_window.setActive(true);

    m_game.sfgui_wrap.Display(m_game.m_window);


	m_game.m_window.display();
}

void PlayState::registerActions() {
    actionMap["up"] = Action(sf::Keyboard::W, Action::Hold);
    actionMap["down"] = Action(sf::Keyboard::S, Action::Hold);
    actionMap["left"] = Action(sf::Keyboard::A, Action::Hold);
    actionMap["right"] = Action(sf::Keyboard::D, Action::Hold);
    actionMap["openMenu"] = Action(sf::Keyboard::M, Action::PressOnce);
    actionMap["openDevConsole"] = Action(sf::Keyboard::P, Action::PressOnce);
    actionMap["close"] = Action(sf::Event::Closed);
    actionMap["escape"] = Action(sf::Keyboard::Escape, Action::PressOnce);
    actionMap["dig"] = Action(sf::Keyboard::Space, Action::Hold);
    actionMap["dig-up"] = actionMap["up"] && actionMap["dig"];
    actionMap["dig-down"] = actionMap["down"] && actionMap["dig"];
    actionMap["dig-left"] = actionMap["left"] && actionMap["dig"];
    actionMap["dig-right"] = actionMap["right"] && actionMap["dig"];
    actionMap["zoom"] = Action(sf::Event::MouseWheelScrolled);

    callbackSystem.connect("zoom", ZoomAction(screenView));
}

void PlayState::updateInput(){

    // Clear events from last frame
    actionMap.clearEvents();

    // Forward all events to the action map
    sf::Event event;
    while (m_game.m_window.pollEvent(event)) {
        actionMap.pushEvent(event);
        m_game.desktop.HandleEvent( event );
    }

    /* Key Bindings */

    thor::UniversalEmitter* emitter = nullptr;

    if(actionMap.isActive("dig-up")){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x,pos.y-1);
		emitter = tileMap.digBlock(newPos,player.damagePerTick);
	}
	else if(actionMap.isActive("dig-left")){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x-1,pos.y);
        emitter = tileMap.digBlock(newPos,player.damagePerTick);
	}
	else if(actionMap.isActive("dig-down")){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x,pos.y+1);
        emitter = tileMap.digBlock(newPos,player.damagePerTick);
	}
	else if(actionMap.isActive("dig-right")){
		sf::Vector2<int> pos = player.getCurrentGridPosition();
		sf::Vector2<int> newPos = sf::Vector2<int>(pos.x+1,pos.y);
		emitter = tileMap.digBlock(newPos,player.damagePerTick);
	}


    if (actionMap.isActive("left")){
        player.setMovement("LEFT");
    }
    else if (actionMap.isActive("down")){
        player.setMovement("DOWN");
    }
		else if (actionMap.isActive("right")){
        player.setMovement("RIGHT");
    }
		else if (actionMap.isActive("up")){
        player.setMovement("UP");
    }
		else{
			player.setMovement("NEUTRAL");
		}
    if (actionMap.isActive("openMenu")){
        m_next = m_game.build<MenuState>( false );
    }
    if (actionMap.isActive("openDevConsole")){
        onHideWindowClicked();
    }
    if (actionMap.isActive("close")) {
        m_game.quit();
    }
    if (actionMap.isActive("escape")) {
        m_music.stop();
        stateChangeCleanup();
        m_next = m_game.build<MainMenuState>( true );
    }

    actionMap.invokeCallbacks(callbackSystem, &m_game.m_window);

    if(emitter != nullptr) {
        particleSystem.addEmitter(*emitter,sf::seconds(.8));
        emitter = nullptr;
    }

    delete emitter;

}

void PlayState::createParticleTexture(int w, int h) {
    /* Create an empty texture of specified size */
    particleTexture.create(w,h);

    /* 4 because pixels have 4 components (RGBA) */
    sf::Uint8* pixels = new sf::Uint8[w * h * 4];

    /* Add color to the pixels */
    for(register int i = 0; i < w*h*4; i += 4) {
        pixels[i] = 255;
        pixels[i+1] = 255;
        pixels[i+2] = 255;
        pixels[i+3] = 255;
    }

    particleTexture.update(pixels);
}

void PlayState::animateParticles() {
    sf::Vector2f scaler(3.f,4.f);
    thor::ScaleAffector scaleAffector(scaler);
    particleSystem.addAffector(scaleAffector);

    sf::Vector2f acceleration(-500.f, 0.f);
    thor::ForceAffector gravityAffector(acceleration);
    particleSystem.addAffector(gravityAffector);

    thor::FadeAnimation fader(0.1f, 0.1f);
    particleSystem.addAffector( thor::AnimationAffector(fader));

    /*
    thor::ColorGradient gradient;
    gradient[0.f] = sf::Color(0, 0, 0, 100);
    //gradient[0.5f] = sf::Color(0, 150, 100);
    gradient[1.f] = sf::Color(255, 255, 255, 100);
    thor::ColorAnimation colorizer(gradient);
    particleSystem.addAffector( thor::AnimationAffector(colorizer));
    */
}

void PlayState::createDevConsole() {
    devConsole_screen = sfg::Window::Create(sfg::Window::Style::TITLEBAR | sfg::Window::Style::BACKGROUND | sfg::Window::Style::CLOSE);
    devConsole_screen->SetId("devConsole");
    devConsole_screen->SetTitle("Dev Console");
    devConsole_screen->SetPosition(sf::Vector2f(100.f,200.f));

    auto box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );

    auto resetBtn = sfg::Button::Create();
    auto toggleGridBtn = sfg::Button::Create();
    auto speedUpBtn = sfg::Button::Create();
    auto slowDownBtn = sfg::Button::Create();
    auto playerDamageScale = sfg::Scale::Create( sfg::Scale::Orientation::HORIZONTAL );
    auto wallResetScale = sfg::Scale::Create( sfg::Scale::Orientation::HORIZONTAL );

    playerDamageScaleLabel = sfg::Label::Create();
    playerDamageScaleLabel->SetText( "Player Damage: " + std::to_string(player.damagePerTick) );

    playerDamageAdjustment = playerDamageScale->GetAdjustment();
    playerDamageAdjustment->SetValue(player.damagePerTick);
    playerDamageAdjustment->SetLower( 0.f );
    playerDamageAdjustment->SetUpper( 20.f );

    wallResetScaleLabel = sfg::Label::Create();
    wallResetScaleLabel->SetText( "Wall: " + std::to_string(wallReset) );

    wallResetAdjustment = wallResetScale->GetAdjustment();
    wallResetAdjustment->SetLower( 10.f );
    wallResetAdjustment->SetUpper( 100.f );

    playerDamageScale->SetRequisition( sf::Vector2f( 80.f, 20.f ) );
    wallResetScale->SetRequisition( sf::Vector2f( 80.f, 20.f ) );

    playerDamageAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &PlayState::playerDamageScaleAdjustmentChange, this ) );
    wallResetAdjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &PlayState::wallResetAdjustmentChange, this ) );
    resetBtn->GetSignal( sfg::Window::OnLeftClick ).Connect( std::bind( &PlayState::onResetBtnClicked, this ) );
    toggleGridBtn->GetSignal( sfg::Window::OnLeftClick ).Connect( std::bind( &PlayState::onToggleGridBtnClicked, this ) );

    resetBtn->SetLabel( "Reset to Origin" );
    toggleGridBtn->SetLabel( "Toggle Grid" );
    speedUpBtn->SetLabel( "Speed it Up" );
    slowDownBtn->SetLabel( "Slow it Down" );

    box->Pack(resetBtn);
    box->Pack(toggleGridBtn);
    box->Pack(speedUpBtn);
    box->Pack(slowDownBtn);
    box->Pack(playerDamageScaleLabel);
    box->Pack(playerDamageScale);
    box->Pack(wallResetScaleLabel);
    box->Pack(wallResetScale);

    box->SetSpacing( 5.f );

    devConsole_screen->Add(box);

    devConsole_canvas = sfg::Canvas::Create();
    devConsole_screen->Add(devConsole_canvas);
    devConsole_canvas->SetRequisition(sf::Vector2f(200.f,300.f));

    m_game.desktop.Add(devConsole_screen);
    m_game.desktop.Update(frameTime);

    devConsole_screen->GetSignal( sfg::Window::OnCloseButton ).Connect( std::bind( &PlayState::onHideWindowClicked, this ) );
}

void PlayState::stateChangeCleanup() {
    m_game.desktop.Remove(devConsole_screen);
    m_game.desktop.Remove(devConsole_canvas);
    devConsole_screen.reset();
    devConsole_canvas.reset();
    playerDamageScaleLabel.reset();
    playerDamageAdjustment.reset();
    wallResetScaleLabel.reset();
    wallResetAdjustment.reset();
    std::cout << "Desktop Cleanup" << std::endl;
}


/* SFGUI elements */

void PlayState::playerDamageScaleAdjustmentChange() {
    std::stringstream sstr;
    sstr << playerDamageAdjustment->GetValue();
    playerDamageScaleLabel->SetText( "Player Damage: " + sstr.str() );
    player.damagePerTick = playerDamageAdjustment->GetValue();
}

void PlayState::wallResetAdjustmentChange() {
    std::stringstream sstr;
    sstr << wallResetAdjustment->GetValue();
    wallResetScaleLabel->SetText( "Wall: " + sstr.str() );
    wallReset = wallResetAdjustment->GetValue();
}

void PlayState::onResetBtnClicked() {
    wall = 0;
    player.warp(sf::Vector2<int>(10,0));
}

void PlayState::onToggleGridBtnClicked() {
    tileMap.toggleGrid();
}

void PlayState::onHideWindowClicked() {
    if(m_game.getDevMode()) {
        devConsole_screen->Show(!devConsole_screen->IsLocallyVisible());
    }
}

/* End SFMLGUI elements */

/* Thor System Callback Functions */
/*
void PlayState::onZoom(thor::ActionContext<std::string> context) {
    sf::Event event = *context.event;
}
*/
/* End Thor System Callback Function */
