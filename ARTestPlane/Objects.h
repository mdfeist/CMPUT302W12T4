/**
 * Objects.h
 * Created By: Michael Feist
 */

#include <osg/Geode>

/*
 * Able to create simple objects.
 */
namespace Objects
{
	osg::Geode *createPlane();
	void applyTexture(char *texturePath, osg::Node *node);
};