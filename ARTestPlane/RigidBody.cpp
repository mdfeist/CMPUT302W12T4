/**
 * RigidBody.cpp
 * Created By: Michael Feist
 */

#include "RigidBody.h"

RigidBody::RigidBody(void)
{
}


RigidBody::~RigidBody(void)
{
}

void RigidBody::addFrame(osg::Vec3 position, osg::Vec4 rotation)
{
	this->_transform->setPosition(position);
	this->_transform->setRotation(rotation);
}