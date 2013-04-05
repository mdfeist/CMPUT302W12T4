/**
 * Application.cpp
 * Created By: Michael Feist
 */
#include "Application.h"

#include <osg/AutoTransform>
#include <osg/Texture2D>
#include <osg/TexMat>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

#include "Client.h"

#include "RigidBody.h"
#include "Objects.h"
#include "KeyBoardInput.h"
#include "GenericInput.h"

#include "XBoxThread.h"

#include "Settings.h"

osgViewer::Viewer viewer;
osg::Vec4 backGroundColor(0.f, 0.f, 0.f, 0.f);

osg::AutoTransform* planeMatrix;
osg::AutoTransform* cameraMatrix;

int Application::run()
{
	Settings::open();

	XBoxThread::startThread();

	ClientHandler* theClient = 0;
	Client::createClient(&theClient);

	osg::Group* rootNode = new osg::Group();
	planeMatrix = new osg::AutoTransform();
	cameraMatrix = new osg::AutoTransform();

	RigidBody *cameraBody = new RigidBody();
	cameraBody->setTransform(cameraMatrix);

	//theClient->addRigidBody(65537, planeBody);
	theClient->addRigidBody(65537, cameraBody);

	rootNode->addChild(planeMatrix);
	//planeMatrix->setPosition(osg::Vec3(-5.f, -5.5f, -5.f));
	planeMatrix->setScale(10.f);

	osg::Geode *plane = Objects::createPlane();
	planeMatrix->addChild(plane);
	
	Objects::applyTexture("Images/checker.jpg", plane);

	osg::Camera* cam = new osg::Camera();
	cam->setClearColor(backGroundColor);
	cam->addChild(rootNode);

	viewer.setCamera(cam);

	viewer.setRunMaxFrameRate(60.f);

	viewer.setUpViewInWindow(100, 100, 800, 600);

	float fov, aspect;

	Settings::getCameraFOV(&fov);
	Settings::getCameraAspectRatio(&aspect);

	// Keyboard input
	KeyBoardInput* kboard = new KeyBoardInput();
	GenericInput::setFOV(fov);
	GenericInput::setAspect(aspect);

	GenericInput::setCameraOffsetX(0.f);
	GenericInput::setCameraOffsetY(0.f);
	GenericInput::setCameraOffsetZ(0.f);

	viewer.addEventHandler(kboard);

	viewer.realize();
	
	int c = 0; 

	// Main Loop
	while( !viewer.done() )
	{
		c++;

		cam->setProjectionMatrixAsPerspective(GenericInput::getFOV(), 
			GenericInput::getAspect(), 0.5, 1000.f);

		osg::Quat quat = cameraMatrix->getRotation();

		osg::Matrixf matrix = cam->getViewMatrix();
		matrix.setRotate(osg::Quat(quat.x(), -quat.y(), -quat.z(), quat.w()));
		matrix.setTrans(osg::Vec3(-cameraMatrix->getPosition().x(), 
			cameraMatrix->getPosition().y(), 
			cameraMatrix->getPosition().z()));
		cam->setViewMatrix(osg::Matrixf::inverse(matrix));

		osg::Vec3 eye;
		osg::Vec3 center;
		osg::Vec3 up;

		cam->getViewMatrixAsLookAt(eye, center, up);
		
		if (c % 10 == 0) {
			printf("X: %f Y: %f Z: %f\n", GenericInput::getCameraOffsetX(), 
				GenericInput::getCameraOffsetY(), GenericInput::getCameraOffsetZ());
			printf("FOV: %f\nAspect: %f\n",
				GenericInput::getFOV(), GenericInput::getAspect());

			/*
			printf("Eye: %f %f %f\nCenter: %f %f %f\nUp: %f %f %f\n",
				eye.x(), eye.y(), eye.z(), center.x(), center.y(), center.z(),
				up.x(), up.y(), up.z());
				*/
		}
		 
		viewer.frame();
	}

	Client::deleteClient(&theClient);

	return 0;
}
