/**
 * Objects.h
 * Created By: Michael Feist
 */

#include <osg/Geode>
#include <string.h>
/*
 * Able to create simple objects.
 */
namespace Objects
{
	osg::Geode *createPlane();
	void applyTexture(std::string texturePath, osg::Node *node);
};