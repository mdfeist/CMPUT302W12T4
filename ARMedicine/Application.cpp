/**
 * Application.cpp
 * Created By: Michael Feist
 */

#include "Application.h"

//#include "SimpleOSGRender.h"
#include "Util.h"
#include "HUD.h"

#include <Windows.h>
#include <stdio.h>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

osgViewer::Viewer viewer;

osg::Vec4 backGroundColor(0.2f,0.2f,0.4f,1.0f);

int Application::run()
{

	osg::Group* rootNode = new osg::Group();
	
	// HUD
	HUD *hud = new HUD();
	hud->createPlane(osg::Vec4(0, 0, 1000, 200), osg::Vec4(1.0f,0.2f,0.5f,1.0f));
	hud->createTitle("ARMedicine");

	rootNode->addChild(hud->getCamera());

	// Cow
	osg::Node* model = osgDB::readNodeFile("cow.osg"); 
	rootNode->addChild(model);

	viewer.setSceneData(rootNode);

	// Set Background color
	viewer.getCamera()->setClearColor(backGroundColor);

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();

	// Start main loop
	while( !viewer.done() )
	{
		viewer.frame();
	}

	return 0;
}