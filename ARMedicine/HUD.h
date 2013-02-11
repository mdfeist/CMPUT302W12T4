#pragma once

#include <osg/ShapeDrawable>

#include <osgText/Font>
#include <osgText/Text>

class HUD
{
public:
	HUD(void);
	HUD(int w, int h);
	~HUD(void);

	osg::Camera* getCamera();
	void createTitle(const std::string& l);
	void createPlane(osg::Vec4 dim, osg::Vec4 color);

private:
	osg::Camera* camera;
	osg::Geode* geode;
	osgText::Font* font;

	int width, height;

	void init();
	osg::Camera* createOrthoCamera(double width, double height);
	osgText::Text* createLabel(const std::string& l, osgText::Font* font, osg::Vec2 position, unsigned int size);
};

