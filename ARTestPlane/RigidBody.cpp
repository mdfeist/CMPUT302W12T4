 #include "RigidBody.h"

RigidBody::RigidBody(void)
{
}


RigidBody::~RigidBody(void)
{
}

void RigidBody::addFrame(osg::Vec3 position, osg::Vec4 rotation)
{
	/*
	osg::Vec4 newRotation;

	float averageDistance = 0;

	for (int i = 0; i < MAX_FRAMES - 1; i++)
	{
		averageDistance += (this->_rotation[i + 1] - this->_rotation[i]).length();
	}

	averageDistance /= MAX_FRAMES - 1;

	float diff = (rotation -  this->_rotation[0]).length() / (1.25*averageDistance);

	if (diff <= 1.0f)
	{
		newRotation = rotation;
	} else
	{
		newRotation = averageDistance*(rotation -  this->_rotation[0]).normalize() + this->_rotation[0];
	}

	for (int i = MAX_FRAMES - 2; i >= 0; i--)
	{
		this->_rotation[i + 1] = this->_rotation[i];
	}
	
	this->_rotation[0] = newRotation;
	*/
	this->_transform->setPosition(position);
	this->_transform->setRotation(rotation);
}