/**
 * Application.cpp
 * Created By: Michael Feist
 */

#include "Application.h"

//#include "SimpleOSGRender.h"
#include "Util.h"
#include "SetupViews.h"

#include <Windows.h>
#include <stdio.h>

#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
//#include <osgGA/TrackballManipulator>

#include <osg/io_utils>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgWidget/Util>
#include <osgWidget/WindowManager>
#include <osgWidget/Box>
#include <osgWidget/Canvas>
#include <osgWidget/Label>
#include <osgWidget/ViewerEventHandlers>

osgViewer::Viewer viewer;

osg::Vec4 backGroundColor(0.2f,0.2f,0.4f,1.0f);

const unsigned int MASK_2D = 0xF0000000;
const unsigned int MASK_3D = 0x0F000000;

void bound(osg::Node* node) {
    osg::BoundingSphere bs = node->getBound();

    osgWidget::warn() << "center: " << bs.center() << " radius: " << bs.radius() << std::endl;
}

int Application::run()
{
	int width, height;
	Util::getDesktopResolution(width, height);

	osg::Group* rootNode = new osg::Group();

	osgWidget::WindowManager* wm = new osgWidget::WindowManager(
        &viewer,
        width,
        height,
        MASK_2D //,
        //osgWidget::WindowManager::WM_USE_RENDERBINS
    );

	SetupViews::init(wm);

	osg::Camera* camera = wm->createParentOrthoCamera();

    rootNode->addChild(camera);
	
    viewer.addEventHandler(new osgWidget::MouseHandler(wm));
    viewer.addEventHandler(new osgWidget::KeyboardHandler(wm));
    viewer.addEventHandler(new osgWidget::ResizeHandler(wm, camera));
    viewer.addEventHandler(new osgWidget::CameraSwitchHandler(wm, camera));
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(
        viewer.getCamera()->getOrCreateStateSet()
    ));

    wm->resizeAllWindows();

	// Cow
	osg::Node* model = osgDB::readNodeFile("cow.osg"); 
	rootNode->addChild(model);

	viewer.setSceneData(rootNode);

	// rootNode->removeChild(model);

	// Set Background color
	viewer.getCamera()->setClearColor(backGroundColor);

	viewer.setRunMaxFrameRate(60.f);

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();

	// Start main loop
	while( !viewer.done() )
	{
		viewer.frame();
	}

	return 0;
}