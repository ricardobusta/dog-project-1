/*
 * debugscene.cpp
 *
 *  Created on: 08/09/2010
 *      Author: Cle�bulo
 */

#include "debugscene.h"

#include "../entities/projectile.h"
#include "../entities/hero.h"
#include "../entities/box.h"

DebugScene::DebugScene()
{
	up = down = left = right = shooting = false;
	backgroundMusic = NULL;
}

DebugScene::~DebugScene() {
}

bool DebugScene::load()
{
#ifdef LINUX
	//carregando musica de fundo
	this->backgroundMusic = SDL::loadBackgroundMusic("/sounds/background.ogg");

	//carrega efeito sonoro de tiro
	this->efeitosSonoros.push_back(SDL::loadSound("/sounds/laser.ogg"));
#endif
#ifdef WIN
	//carregando musica de fundo
	this->backgroundMusic = SDL::loadBackgroundMusic("\sounds\background.ogg");

	//carrega efeito sonoro de tiro
	this->efeitosSonoros.push_back(SDL::loadSound("\sounds\laser.ogg"));
#endif

	return true;
}

bool DebugScene::prepare()
{
	// Preparando os elementos
	ship = new Hero;
	this->entities.push_back( ship );

	Box *gun = new Box(ship);
	gun->randomColors();
	gun->setData(20,1,20);
	gun->toggleFrozen(); //Freezes the box in place
	gun->setPosition( Point3(0,40,-10) );

	// Posicionando a c�mera
	camera->moveOriginW( Vector3( -320.0f , -240.0f , 100.0f ) );
	camera->setRotationX( -90*16 );
	//camera.setRotationX( 30 );

	Box* cen;
	for( int i = 0 ; i < 3 ; i++ ){
		cen = new Box;
		cen->randomColors();
		cen->setData(70,20,130);
		cen->move(Vector3(0,-100, -i*260));
		this->entities.push_back( cen );

		cen = new Box;
		cen->randomColors();
		cen->setData(70,20,130);
		cen->move(Vector3(80,-100, -i*260-100));
		this->entities.push_back( cen );

		cen = new Box;
		cen->randomColors();
		cen->setData(70,20,130);
		cen->move(Vector3(-80,-100, -i*260-100));
		this->entities.push_back( cen );
	}

	//inicia a execucao da musica de fundo
	SDL::playBackgroundMusic(backgroundMusic);

	return true;
}

bool DebugScene::unload()
{
	list<Entity*>::iterator it;

	while (!entities.empty()){
			it = entities.begin();
			delete (*it);
			entities.pop_front();
		}

	return true;
}

void DebugScene::input()
{
	// The main inputs
	while( SDL::actionsLeft() ){

		// The next action
		switch( SDL::nextAction() ){

			// Close the game action
			case CON_QUIT_GAME:
				// End the scene
				this->running = false;
				break;

			// Directional
			case CON_UP_ON:
				up = true;
				ship->addAction( CON_UP_ON );
				break;
			case CON_UP_OFF:
				up = false;
				ship->addAction( CON_UP_OFF );
				break;
			case CON_DOWN_ON:
				down = true;
				ship->addAction( CON_DOWN_ON );
				break;
			case CON_DOWN_OFF:
				down = false;
				ship->addAction( CON_DOWN_OFF );
				break;
			case CON_LEFT_ON:
				left = true;
				ship->addAction( CON_LEFT_ON );
				break;
			case CON_LEFT_OFF:
				left = false;
				ship->addAction( CON_LEFT_OFF );
				break;
			case CON_RIGHT_ON:
				right = true;
				ship->addAction( CON_RIGHT_ON );
				break;
			case CON_RIGHT_OFF:
				right = false;
				ship->addAction( CON_RIGHT_OFF );
				break;
			case CON_SHOOTING_ON:
				shooting = true;
				ship->addAction( CON_SHOOTING_ON );
				break;
			case CON_SHOOTING_OFF:
				shooting = false;
				ship->addAction( CON_SHOOTING_OFF );
				break;

			default:
				// Standby
				break;
		}
	}
}

void DebugScene::logic()
{
	// Moving the camera
	//camera.moveOriginW( Vector3(0,0,-5) );

	//if( up ) ship->rotate(-10,0,0);
	//if( down ) ship->rotate(10,0,0);
	float speed = 5;
	if( up ) ship->move( Vector3(0,0,-speed) );
	if( down ) ship->move( Vector3(0,0,speed) );
	if( right ) ship->move( Vector3(speed,0,0) );
	if( left ) ship->move( Vector3(-speed,0,0) );

	if( shooting ){
		//toca o efeito sonoro de tiro
		/*if(!(SDL::playSound(efeitosSonoros[0])))
		{
			printf("Erro ao tocar o som\n");
		}*/

		if(ship->shootCoolDown<=0){
			Projectile *p = new Projectile( Vector3(0,0,-10) );
			p->setPosition( *ship->getPosition() );
			this->entities.push_back( p );
			ship->shootCoolDown = 10;
		}
	}
	//ship->move( Vector3(0,0,-5) );
	handleEntities();
}

void DebugScene::render()
{
	// Render start
	SDL::prepareRender();

	//Position the objects in the camera
	glMultMatrixf( camera->getMatrixToThis() );

	// Render all the elements of the scene
	list<Entity*>::iterator it;
	for(it=entities.begin();it!=entities.end();it++){
		(*it)->render();
	}
	// Switch the buffers
	SDL::switchBuffers();
}

SceneMessage DebugScene::result()
{
	// End the execution of the game
	return SCN_END_GAME;
}

