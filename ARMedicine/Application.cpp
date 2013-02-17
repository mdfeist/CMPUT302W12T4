/**
 * Application.cpp
 * Created By: Michael Feist
 */

#include "Application.h"

//#include "SimpleOSGRender.h"
#include "Util.h"
#include "TabBar.h"
#include "UIButton.h"

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

	//TabBar* notebook1 = new TabBar("notebook1");
	//wm->addChild(notebook1);

	// Title Bar
	osgWidget::Box* titleBar = new osgWidget::Box(std::string("Title Bar"),
		osgWidget::Box::HORIZONTAL,
            false);

	// Title
	osgWidget::Label* title = new osgWidget::Label("title", "ARMedicine");
	title->setFont("fonts/segoeui.ttf");
	title->setFontSize(42);
	title->setColor(0.3f,0.57f,1.0f,1.0f);
	title->setCanFill(true);
	title->setSize(width - 250.0f, 150.0f);

	titleBar->setPosition(osgWidget::Point(-width/2.f + 250.f, height - 160.0f, 0));

	titleBar->addWidget(title);
	wm->addChild(titleBar);

	// Menu Button
	UIButton* button = new UIButton("Menu");
	button->setPadLeft(10);
	button->setPadRight(5);

	// 3D Model Button
	button->setPadBottom(10);
	UIButton* button2 = new UIButton("3D Model");
	button2->setPadBottom(10);

	// Menu Bar
	osgWidget::Box* menuBar = new osgWidget::Box(std::string("Menu Bar"),
			osgWidget::Box::HORIZONTAL,
            true);
	
	menuBar->getBackground()->setColor(0, 0, 0, 0);
	menuBar->addWidget(button);
	menuBar->addWidget(button2);

	wm->addChild(menuBar);

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

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();

	// Start main loop
	while( !viewer.done() )
	{
		viewer.frame();
	}

	return 0;
}