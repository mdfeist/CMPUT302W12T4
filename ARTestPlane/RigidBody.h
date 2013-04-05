/**
 * RigidBody.h
 * Created By: Michael Feist
 */

#pragma once

#include <osg/AutoTransform>

#include "NatNetTypes.h"

/*
 * The RigidBody class handles transformation data
 * of a single rigid body.
 */
class RigidBody
{
private:
	osg::AutoTransform* _transform;

public:
	RigidBody(void);
	~RigidBody(void);

	/*
	 * Set the transformation of the rigidbody.
	 * Make sure the AutoTransform is attached
	 * to the osg model.
	 */
	void setTransform(osg::AutoTransform* transform) { this->_transform = transform; }
	// Update the transformation of the rigidbody
	void addFrame(osg::Vec3 position, osg::Vec4 rotation);
};

