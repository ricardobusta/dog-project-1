/*
 * projectile.cpp
 *
 *  Created on: 16/09/2010
 *      Author: ricardo
 */

#include "projectile.h"

Projectile::Projectile(Vector3 d, Entity* p):Particle(p) {
	// TODO Auto-generated constructor stub
	direction = new Vector3;
	*direction = d;
	lifeTime = 25;
}

Projectile::~Projectile() {
	// TODO Auto-generated destructor stub
}

void Projectile::draw(){
	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(10,0,0);
		glVertex3f(10,0,-10);
		glVertex3f(0,0,-10);
	glEnd();
}

void Projectile::handleSelf(){
	this->move(*direction);
	lifeTime--;
	if(lifeTime<=0){
		toggleLive();
	}
}