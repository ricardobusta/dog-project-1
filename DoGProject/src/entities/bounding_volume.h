/*
 * bounding_volume.h
 *
 *  Created on: 21/09/2010
 *      Author: Shade
 */

#include "../base/sdl.h"
#include "../math/point3.h"


#ifndef BOUNDING_VOLUME_H_
#define BOUNDING_VOLUME_H_

class BoundingBox;

class BoundingVolume {
public:
	BoundingVolume();
	virtual ~BoundingVolume();

	virtual void draw()=0;
	virtual void setCurPosition(Point3 pos)=0;
	virtual bool checkCollision(BoundingBox *box)=0;
};

class BoundingBox : public BoundingVolume {
public:
	BoundingBox(Point3 position, float width, float height, float depth);
	BoundingBox(float x, float y, float z, float width, float height, float depth);
//	BoundingBox(Point3 *position, Point3 max, Point3 min);
//	BoundingBox(Point3 position, Point3 max, Point3 min);
	~BoundingBox();

	void draw();
	void drawFaces(int index, float x, float y, float z,float halfwidth, float halfheight, float halfdepth);
	bool checkCollision(BoundingBox *collisionBox);
	void updateBoundaries();

	void setCurPosition(Point3 position);

	Point3 getCurPosition();
	float getBoxSize();

	Point3 getMax();
	Point3 getMin();

private:
	Point3 *cur_position;
	float height;
	float width;
	float depth;

	Point3 max;
	Point3 min;

	bool colliding;

};

/* todo class BoundingSphere : public BoundingVoulume{
public:
	BoundingSphere(Point3 position, float radius);
	~BoundingSphere();
};*/

#endif /* BOUNDING_VOLUME_H_ */