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
	delete direction;
	// TODO Auto-generated destructor stub
}

void Projectile::handler(){
	this->move(*direction);
	lifeTime--;
	if(lifeTime<=0 and isLive()){
		toggleLive();
	}
}