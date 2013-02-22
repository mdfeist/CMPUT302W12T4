#include "Application.h"

#include "Client.h"

#include <osg/AutoTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

osgViewer::Viewer viewer;
osg::Vec4 backGroundColor(0.f, 0.f, 0.f, 0.f);

osg::AutoTransform* planeMatrix;

int Application::run()
{
	Client::initClient();

	osg::Group* rootNode = new osg::Group();
	planeMatrix = new osg::AutoTransform();

	Client::addRigidBody(1, planeMatrix);

	rootNode->addChild(planeMatrix);

	osg::Node* model = osgDB::readNodeFile("cow.osg");
	planeMatrix->addChild(model);

	viewer.setSceneData(rootNode);
	viewer.getCamera()->setClearColor(backGroundColor);

	viewer.setRunMaxFrameRate(60.f);

	viewer.setUpViewInWindow(100, 100, 800, 600);

	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();
	
	//Loop
	while( !viewer.done() )
	{
		viewer.frame();
	}

	Client::cleanClient();

	return 0;
}
