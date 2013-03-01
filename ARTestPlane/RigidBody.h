/**
 * RigidBody.h
 * Created By: Michael Feist
 */

#pragma once

#include <osg/AutoTransform>

#include "NatNetTypes.h"
//#include "Marker.h"

#define MAX_FRAMES 8

class RigidBody
{
private:
	osg::AutoTransform* _transform;
	osg::Vec4 _rotation[MAX_FRAMES];
	//Marker _markers[MAX_RBMARKERS][MAX_FRAMES];

public:
	RigidBody(void);
	~RigidBody(void);

	void setTransform(osg::AutoTransform* transform) { this->_transform = transform; }
	void addFrame(osg::Vec3 position, osg::Vec4 rotation);
};

